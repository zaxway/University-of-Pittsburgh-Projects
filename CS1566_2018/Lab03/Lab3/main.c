/*
 * triangle.c
 *
 *  Created on: Aug 28, 2017
 *      Author: Thumrongsak Kosiyatrakul
 */


#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>


#else // non-Mac OS X operating systems

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include "initShader.h"
#include <math.h>
#include <time.h>

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} vec4;

int num_vertices;

vec4 v4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    vec4 result = {x, y, z, w};
    return result;
}

vec4 *circle(int *num_vertices)
{
    float theta, theta_r, theta10_r;
    int index = 0;
    
    *num_vertices = 216;
    vec4 *vertices = (vec4 *) malloc (sizeof(vec4) * 216);
    
    for(theta = 0; theta <= 350; theta = theta + 10)
    {
        theta_r = theta * M_PI / 180.0;
        theta10_r = (theta + 10) * M_PI / 180.0;
        
        vertices[index] = v4(0.0, 0.0, 0.0, 1.0);
        vertices[index + 1] = v4(cos(theta_r), sin(theta_r), 0.0, 1.0);
        vertices[index + 2] = v4(cos(theta10_r), sin(theta10_r), 0.0, 1.0);
        index += 3;
    }
    
    for(theta = 0; theta <= 350; theta = theta + 10)
    {
        theta_r = theta * M_PI / 180.0;
        theta10_r = (theta + 10) * M_PI / 180.0;
        
        vertices[index] = v4(0.0, 0.0, 1.0, 1.0);
        vertices[index + 1] = v4(cos(theta_r), sin(theta_r), 0.0, 1.0);
        vertices[index + 2] = v4(cos(theta10_r), sin(theta10_r), 0.0, 1.0);
        index += 3;
    }
    
    
    return vertices;
}

vec4 *genRandomTriangleColors(int num_vertices)
{
    GLfloat r, g, b;
    int index = 0, i;
    
    srand(time(0));
    
    vec4 *colors = (vec4 *) malloc(sizeof(vec4) * num_vertices);
    
    for(i = 0; i < num_vertices / 3; i++)
    {
        r = rand() / (float) RAND_MAX;
        g = rand() / (float) RAND_MAX;
        b = rand() / (float) RAND_MAX;
        
        colors[index] = v4(r, g, b, 1.0);
        colors[index + 1] = v4(r, g, b, 1.0);
        colors[index + 2] = v4(r, g, b, 1.0);
        index += 3;
    }
    
    return colors;
}

void init(void)
{
    GLuint program = initShader("/Users/mohitjain/Documents/CS1566_2018/Lab3/Lab3/vshader.glsl", "/Users/mohitjain/Documents/CS1566_2018/Lab3/Lab3/fshader.glsl");
    glUseProgram(program);
    
    int circle_num_vertices;
    vec4 *circle_vertices = circle(&circle_num_vertices);
    vec4 *circle_colors = genRandomTriangleColors(circle_num_vertices);
    num_vertices = circle_num_vertices;
    
    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * 2 * num_vertices, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * num_vertices, circle_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices, sizeof(vec4) * num_vertices, circle_colors);
    
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    
    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices));
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q') {
        exit(0);
    }
    else if(key == 'r')
    {
        float thirtyr = 30 * M_PI / 180;
        //mat4 m = {{cos(thirtyr), -sin(thirtyr), 0, 0}, {sin(thirtyr), cos(thirtyr), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        //tr_matrix = m; // we only send the translation matrix into the database
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Triangle");
    //glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
