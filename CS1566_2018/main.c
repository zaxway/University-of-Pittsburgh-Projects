/*
 * triangle.c
 *
 *  Created on: 10/12/17
 *      Author: Mohit Jain
 */


#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
//#else // non-Mac OS X operating systems
//
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include "initShader.h"
#include <time.h>
//#include "LabAssignment1.c"

#include <stdio.h>

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))




typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} vec4;

typedef struct
{
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
} mat4;

typedef struct {
    int mouse_x;
    int mouse_y;
    int mouse_button;
    int mouse_state;
} ev;

float lastx = 0.0;
float lasty = 0.0;
float lastz = 0.0;
int left_button_state = 0;

//vec3 vertices[36] =
//// front of the cube
//{{ -0.5,  0.5,  0.0},	// top1
//    {-0.5, -0.5,  0.0},	// bottom left1
//    { 0.5, -0.5,  0.0},	// bottom right1
//    
//    { -0.5,  0.5, 0.0},	// top1
//    {0.5, 0.5, 0.0}, // top2
//    {0.5, -0.5, 0.0}, // bottom right1
//    
//    // top of the cube
//    {-0.5, 0.5, 0.0}, // top1
//    {-0.5, 0.5, -1}, // backtop1 change y to 0.5 after testing
//    {0.5, 0.5, 0.0}, // top2
//    
//    {-0.5, 0.5, -1}, // backtop1 change y to 0.5 after testing
//    {0.5, 0.5, 0.0}, // top2
//    {0.5, 0.5, -1}, // backtop2 change y to 0.5 after testing
//    
//    // right side of the cube
//    {0.5,-0.5,0}, // bottom right1
//    {0.5, 0.5, 0}, // top2
//    {0.5, -0.5, -1}, // backbottom1 x to 0.5
//    
//    {0.5, -0.5, -1}, // backbottom1 x to 0.5
//    {0.5, 0.5, 0}, // top2
//    {0.5, 0.5, -1}, // backtop2 x to 0.5
//    
//    // left side of the cube
//    { -0.5,  0.5,  0.0},	// top1
//    {-0.5, -0.5,  0.0},	// bottom left1
//    {-0.5, -0.5, -1}, // backbottom2 x to -0.5 left side
//    
//    { -0.5,  0.5,  0.0},	// top1
//    {-0.5, -0.5, -1}, // backbottom2 x to -0.5 left side
//    {-0.5, 0.5, -1}, // backtop1 x to -0.5 left side
//    
//    //bottom of the cube
//    {-0.5, -0.5, -1}, // backbottom2 x to -0.5 left side
//    {-0.5, -0.5,  0.0},	// bottom left1
//    { 0.5, -0.5,  0.0},	// bottom right1
//    
//    { 0.5, -0.5,  0.0},	// bottom right1
//    {-0.5, -0.5, -1}, // backbottom2 x to -0.5 left side
//    {0.5, -0.5, -1}, // backbottom1 x to 0.5
//    
//    //back of the cube
//    {0.5, -0.5, -1}, // backbottom1
//    {-0.5, -0.5, -1}, //backbottom2
//    {-0.5, 0.5, -1}, //backtop1
//    
//    {-0.5,0.5,-1}, // backtop1
//    {0.5, -0.5, -1}, //backbottom1
//    {0.5, 0.5, -1}}; //backtop2
//

//vec4 colors[6] =
//{{1.0, 0.0, 0.0, 1.0},	// red   (for top)
//    {0.0, 1.0, 0.0, 1.0},	// green (for bottom left)
//    {0.0, 0.0, 1.0, 1.0}};	// blue  (for bottom right)

//vec4 colors[36] =
//// front of the cube
//{   {1.0, 0, 0.0, 1.0},
//    {1.0, 0, 0.0, 1.0},
//    {1.0, 0, 0.0, 1.0},
//    
//    {1.0, 0.0, 0.0, 1.0},
//    {1.0, 0.0, 0.0, 1.0},
//    {1.0, 0.0, 0.0, 1.0},
//    
//    // top of the cube
//    {0.0, 0, 1, 1.0},
//    {0.0, 0, 1.0, 1.0},
//    {0.0, 0, 1.0, 1.0}, // end of 3
//    
//    {0.0, 0, 1.0, 1.0},
//    {0.0, 0, 1.0, 1.0},
//    {0.0, 0, 1.0, 1.0}, //end of 3
//    
//    //right side of the cube
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0}, // end of 3
//    
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0}, //end of 3
//    
//    // left side of the cube
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0}, // end of 3
//    
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0},
//    {1.0, 1.0, 0.0, 1.0}, //end of 3
//    
//    
//    // bottom of the cube
//    {0.0, 1.0, 0.0, 1.0},
//    {0.0, 1.0, 0.0, 1.0},
//    {0.0, 1.0, 0.0, 1.0}, // end of 3
//    
//    {0.0, 1.0, 0.0, 1.0},
//    {0.0, 1.0, 0.0, 1.0},
//    {0.0, 1.0, 0.0, 1.0}, // end of 3
//    
//    // back of the cube
//    {0.0, 1.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0, 1.0}, // end of 3
//    
//    {0.0, 1.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0, 1.0}}; //end of 3

int num_vertices;

GLuint ctm_location;
mat4 tr_matrix =
{{1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}};

mat4 scaling_matrix =
{{0.98, 0, 0, 0},
    {0, 0.98, 0, 0},
    {0, 0, 0.98, 0},
    {0, 0, 0, 1}};

mat4 scaling_matrix2 =
{{1.02, 0, 0, 0},
    {0, 1.02, 0, 0},
    {0, 0, 1.02, 0},
    {0, 0, 0, 1}};

int enableIdle = 0;
int leftDown = 1;

//mat4 rotate_about_x(float theta);
//mat4 rotate_about_y(float theta);
//mat4 rotate_about_z(float theta);
//mat4 translate(float dx, float dy, float dz);
//mat4 scale(float sx, float sy, float sz);
mat4 m4m4_multiplication(mat4 lm, mat4 rm);
vec4 multiplyByScalarVec(vec4 u, float absu);
vec3 crossProduct(vec3 u, vec3 v);
mat4 m4_transpose(mat4 lm);
vec3 subtractVector(vec3 u, vec3 v);
float dotProduct(vec3 u, vec3 v);
float lengthOfVector(vec3 u);
void printMatrix(mat4 m);

vec4 v4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    vec4 result = {x, y, z, w};
    return result;
}

vec4 *circle(int *num_vertices)
{
    float theta, theta_r, theta10_r;
    int index = 0;
    
    *num_vertices = 116242;
    vec4 *vertices = (vec4 *) malloc (sizeof(vec4) * 116242);
    // cone code
//    for(theta = 0; theta <= 350; theta = theta + 10)
//    {
//        theta_r = theta * M_PI / 180.0;
//        theta10_r = (theta + 10) * M_PI / 180.0;
//        
//        vertices[index] = v4(0.0, 0.0, 0.0, 1.0);
//        vertices[index + 1] = v4(cos(theta_r), sin(theta_r), 0.0, 1.0);
//        vertices[index + 2] = v4(cos(theta10_r), sin(theta10_r), 0.0, 1.0);
//        index += 3;
//    }
//    
//    for(theta = 0; theta <= 350; theta = theta + 10)
//    {
//        theta_r = theta * M_PI / 180.0;
//        theta10_r = (theta + 10) * M_PI / 180.0;
//        
//        vertices[index] = v4(0.0, 0.0, 1.0, 1.0);
//        vertices[index + 1] = v4(cos(theta_r), sin(theta_r), 0.0, 1.0);
//        vertices[index + 2] = v4(cos(theta10_r), sin(theta10_r), 0.0, 1.0);
//        index += 3;
//    }
    // Sphere code
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            index = index + 1;
            vertices[index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            index = index + 1;
        }
    }
    
//    vertices[index] = v4(0.0, 0.0, 1.0, 1.0);
//    index = index + 1;
//    float sin80 = sin(80 * (M_PI/180));
//    float cos80 = cos(80 * (M_PI/180));
//    for (float theta = -180.0; theta <= 180.0; theta += 20.0) {
//        float thetar = theta * (M_PI/180);
//        vertices[index] = v4(sin(thetar) * cos80, cos(thetar) * cos80, sin80, 1.0);
//        index = index + 1;
//    }
//    
//    vertices[index] = v4(0.0, 0.0, -1.0, 1.0);
//    index = index + 1;
//    
//    for(float theta = -180; theta <= 180.0; theta += 20.0) {
//        float thetar = theta;
//        vertices[index] = v4(sin(thetar) * cos80, cos(thetar) * cos80, sin80, 1.0);
//        vertices = vertices + 1;
//    }
    
    
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
    GLuint program = initShader("/Users/mohitjain/Documents/Fall2017/CS1566/Examples/triangle_2/triangle_2/vshader.glsl", "//Users/mohitjain/Documents/Fall2017/CS1566/Examples/triangle_2/triangle_2/fshader.glsl");
    glUseProgram(program);
    
    int circle_num_vertices;
    vec4 *circle_vertices = circle(&circle_num_vertices);
    vec4 *circle_colors = genRandomTriangleColors(circle_num_vertices);
    num_vertices = circle_num_vertices;
    
    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
    
//    GLuint buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * 2 * num_vertices, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * num_vertices, circle_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices, sizeof(vec4) * num_vertices, circle_colors);
    
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    //glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);

    
    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
//    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices));
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices));
    
    ctm_location = glGetUniformLocation(program, "ctm");
    //transformation_matrix = m4_identity();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}
vec4 multiplyByScalarVec(vec4 u, float absu) {
    vec4 result = {(u.x * absu), (u.y * absu), (u.z * absu), (u.w * absu)};
    return result;
}

//mat4 multiplyByScalar(mat4 tr, float c) {
//    mat4 result = {{(tr.x.x * c), 0, 0, 0},{0, tr.y.y * c, 0, 0},{0, 0, tr.z.z * c, 0},{0, 0, 0, tr.w.w * c}};
//    return result;
//}

vec3 crossProduct(vec3 u, vec3 v) {
    float u1, u2, u3, v1, v2, v3;
    float uvi, uvj, uvk;
    u1 = u.x;
    u2 = u.y;
    u3 = u.z;
    v1 = v.x;
    v2 = v.y;
    v3 = v.z;
    uvi = u2 * v3 - v2 * u3;
    uvj = v1 * u3 - u1 * v3;
    uvk = u1 * v2 - v1 * u2;
    vec3 result = {(uvi), (uvj), (uvk)};
    return result;

}

vec3 subtractVector(vec3 u, vec3 v) {
    vec3 result = {(u.x - v.x), (u.y - v.y), (u.z - v.z)};
    //printf("resultx: %f, resulty: %f, resultz: %f", result.x, result.y, result.z);
    return result;
}

float dotProduct(vec3 u, vec3 v)
{
    
    float product = 0.0;
    
    // Loop for calculate cot product
    float productCalc1 = u.x * v.x;
    float productCalc2 = u.y * v.y;
    float productCalc3 = u.z * v.z;
    product = productCalc1 + productCalc2 + productCalc3;
    return product;
}

void printMatrix(mat4 m) {
    printf("%f %f %f %f \n", m.x.x, m.y.x, m.z.x, m.w.x);
    printf("%f %f %f %f \n", m.x.y, m.y.y, m.z.y, m.w.y);
    printf("%f %f %f %f \n", m.x.z, m.y.z, m.z.z, m.w.z);
    printf("%f %f %f %f \n", m.x.w, m.y.w, m.z.w, m.w.w);
    
}

float lengthOfVector(vec3 u) {
    float finalLength = 0.0;
    float sqlength = (u.x * u.x) + (u.y * u.y) + (u.z * u.z);
    //printf("sqlength: %f \n", sqlength);
    finalLength = sqrt(sqlength);
    return finalLength;
}

mat4 m4_transpose(mat4 lm) {
    mat4 result = {
        {lm.x.x, lm.x.y, lm.x.z, lm.x.w},
        {lm.y.x, lm.y.y, lm.y.z, lm.y.w},
        {lm.z.x, lm.z.y, lm.z.z, lm.w.z},
        {lm.w.x, lm.w.y, lm.w.z, lm.w.w}
    };
    
    mat4 rslt = {
        {lm.x.x, lm.y.x, lm.z.x, lm.w.x},
        {lm.x.y, lm.y.y, lm.z.y, lm.w.y},
        {lm.x.z, lm.y.z, lm.z.z, lm.w.z},
        {lm.x.w, lm.y.w, lm.w.z, lm.w.w}
    };
    return rslt;
}

mat4 m4m4_multiplication(mat4 lm, mat4 rm) {
    mat4 result = {{(lm.x.x * rm.x.x + lm.y.x * rm.x.y + lm.z.x * rm.x.z + lm.w.x * rm.x.w),(lm.x.x * rm.y.x + lm.y.x * rm.y.y + lm.z.x * rm.y.z + lm.w.x * rm.y.w),(lm.x.x * rm.z.x + lm.y.x * rm.z.y + lm.z.x * rm.z.z + lm.w.x * rm.z.w),(lm.x.x * rm.w.x + lm.y.x * rm.w.y + lm.z.x * rm.w.z + lm.w.x * rm.w.w)},
        
        {(lm.x.y * rm.x.x + lm.y.y * rm.x.y + lm.z.y * rm.x.z + lm.w.y * rm.x.w),(lm.x.y * rm.y.x + lm.y.y * rm.y.y + lm.z.y * rm.y.z + lm.w.y * rm.y.w),(lm.x.y * rm.z.x + lm.y.y * rm.z.y + lm.z.y * rm.z.z + lm.w.y * rm.z.w),(lm.x.y * rm.w.x + lm.y.y * rm.w.y + lm.z.y * rm.w.z + lm.w.y * rm.w.w)},
        
        {(lm.x.z * rm.x.x + lm.y.z * rm.x.y + lm.z.z * rm.x.z + lm.w.z * rm.x.w),(lm.x.z * rm.y.x + lm.y.z * rm.y.y + lm.z.z * rm.y.z + lm.w.z * rm.y.w),(lm.x.z * rm.z.x + lm.y.z * rm.z.y + lm.z.z * rm.z.z + lm.w.z * rm.z.w),(lm.x.z * rm.w.x + lm.y.z * rm.w.y + lm.z.z * rm.w.z + lm.w.z * rm.w.w)},
        
        {(lm.x.w * rm.x.x + lm.y.w * rm.x.y + lm.z.w * rm.x.z + lm.w.w * rm.x.w),(lm.x.w * rm.y.x + lm.y.w * rm.y.y + lm.z.w * rm.y.z + lm.w.w * rm.y.w),(lm.x.w * rm.z.x + lm.y.w * rm.z.y + lm.z.w * rm.z.z + lm.w.w * rm.z.w),(lm.x.w * rm.w.x + lm.y.w * rm.w.y + lm.z.w * rm.w.z + lm.w.w * rm.w.w)}};
    //printf("%f, %f, %f, %f \n", lm.x.y, rm.x.y, lm.z.x, rm.x.z);
    return result;
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &tr_matrix);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
        exit(0);
    
    if(!enableIdle)
    {
        if(key == 'X')
            tr_matrix.w.x += 0.1;
        else if(key == 'x')
            tr_matrix.w.x -= 0.1;
        else if(key == 'Y')
            tr_matrix.w.y += 0.1;
        else if(key == 'y')
            tr_matrix.w.y -= 0.1;
        else if(key == 'Z')
            tr_matrix.w.z += 0.1;
        else if(key == 'z')
            tr_matrix.w.z -= 0.1;
        else if(key == ' ')
        {
            tr_matrix.w.x = 0.5;
            tr_matrix.w.y = 0.5;
            tr_matrix.w.z = 0.0;
            enableIdle = 1;
        }
        else if(key == 'r')
        {
            float thirtyr = 30 * (180/M_PI);
            mat4 m = {{cos(thirtyr), -sin(thirtyr), 0, 0}, {sin(thirtyr), cos(thirtyr), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
            tr_matrix = m; // we only send the translation matrix into the database
        }
        else if (key == 'o') {
//            mat4 shrink = multiplyByScalar(tr_matrix, 0.98);
            tr_matrix = m4m4_multiplication(scaling_matrix, tr_matrix);
            printf("%f %f %f %f\n", tr_matrix.x.x, tr_matrix.y.x, tr_matrix.z.x, tr_matrix.w.x);
            glutPostRedisplay();
        }
        else if (key == 'l') {
            //mat4 enlarge = multiplyByScalar(tr_matrix, 1.02);
            tr_matrix = m4m4_multiplication(scaling_matrix2, tr_matrix);
            glutPostRedisplay();
        }
        
        glutPostRedisplay();
    }
    else
    {
        if(key == ' ')
        {
            tr_matrix.w.x = 0.0;
            tr_matrix.w.y = 0.0;
            tr_matrix.w.z = 0.0;
            enableIdle = 0;
        }
    }
    
}

void idle(void)
{
    if(enableIdle)
    {
        if(leftDown)
        {
            tr_matrix.w.x -= 0.01;
            tr_matrix.w.y -= 0.01;
            
            if(tr_matrix.w.x < -0.5)
                leftDown = 0;
        }
        else
        {
            tr_matrix.w.x += 0.01;
            tr_matrix.w.y += 0.01;
            
            if(tr_matrix.w.x > 0.5)
                leftDown = 1;
        }
        
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    // x and y are the coordinates of P'
    // want to find z given x and y and the formula x^2 + y^2 + z^2 = 1
    // z = sqrt(1 - x^2 + y^2)
    //x = (x - 256) / 256;
    //y = (y - 256) / -256;
    // calculate for z
    
    float tempx, tempy;
    tempx = (x - 256) / 256.0;
    tempy = (y - 256) / -256.0;
    
    
    float z = 0.0;
    float sq = 1 - (tempx * tempx) - (tempy * tempy);
    if (sq < 0.0) {
        sq = sq * -1;
        z = sqrtf(sq); // initializes the value of coordinate z
        z = z * -1;
    }
    else {
        z = sqrt(sq); // initializes the value of coordinate z
    }
//    tempx = 1;
//    tempy = 2;
//    float z = 3;
//    float testAngle = 45.0 * (180/M_PI);
    
    
    //printf("initialX: %f, initialY: %f, initialZ: %f \n", tempx, tempy, z);
    if (left_button_state == 1) {
        
        vec3 atPointA = {(lastx),(lasty),(lastz)};
        vec3 atPointC = {(tempx), (tempy), (z)};
        
        //vec3 aMinusC = subtractVector(atPointC, atPointA);
        //printf("lengthTest: %f \n", lengthOfaMinusC);
        
        vec3 aMinusC = crossProduct(atPointC, atPointA); // vector of rotation
        float lengthOfaMinusC = lengthOfVector(aMinusC);
        if (lengthOfaMinusC == 0 || lengthOfaMinusC < 0) {
            lengthOfaMinusC = 0.00001;
        }
        vec3 aTimesC = {(aMinusC.x / lengthOfaMinusC), (aMinusC.y / lengthOfaMinusC), (aMinusC.z / lengthOfaMinusC)};
        
        printf("x: %f, y: %f, z: %f \n", aTimesC.x, aTimesC.y, aTimesC.z);
        
        
        // now we have the legs of the triangles/ vector of rotation to calculate angle of rotation
        
        // rotate to y = 0
        float dRotateXhelper = (aTimesC.y * aTimesC.y) + (aTimesC.z * aTimesC.z);
        float dRotateX = sqrt(dRotateXhelper); // this is d
        if (dRotateX == 0) {
            dRotateX = 1;
        }
        printf("dRotateX: %f \n", dRotateX);
        
        float angletoRotateXhelper = aTimesC.z / dRotateX; // z / d
        printf("angleX1: %f \n", angletoRotateXhelper);
        float angleToRotateXhelper2 = aTimesC.y / dRotateX; // y / d
        printf("angleX2: %f \n", angleToRotateXhelper2);
        //double angletoRotateX = acos(angletoRotateXhelper) * (M_PI/180.0);
        
        // rotate to x = 0
        //double angletoRotateY = acos(dRotateX) * (M_PI/180.0);
        
        // this is for rotation of z
        float dotProd = dotProduct(atPointA, atPointC);
        printf("dotProd: %f \n", dotProd);
        if (dotProd > 1 || dotProd < -1) {
            dotProd = -0.9999;
        }
        //float lengthCalc = lengthOfVector(atPointA) * lengthOfVector(atPointC);
        //printf("%f \n", lengthCalc);
        //float acosCalc = dotProd / lengthCalc;
        //printf("%f \n", acosCalc);
        float testAngle = acos(dotProd) * (180/M_PI);
        printf("testAngle: %f \n", testAngle);
        
        // now move the sphere by doing all the necessary calculations
        // get all matrices
        mat4 nRtx = {{1, 0, 0, 0}, {0, angletoRotateXhelper, angleToRotateXhelper2 * -1, 0}, {0, angleToRotateXhelper2, angletoRotateXhelper, 0}, {0, 0, 0, 1}};
        mat4 nRty = {{dRotateX, 0, aTimesC.x * -1, 0}, {0, 1, 0, 0}, {aTimesC.x, 0, dRotateX, 0}, {0, 0, 0, 1}};
        mat4 Rtz = {{cos(testAngle), sin(testAngle), 0, 0}, {sin(testAngle) * -1, cos(testAngle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        mat4 Rty = {{dRotateX, 0, aTimesC.x, 0}, {0, 1, 0, 0}, {aTimesC.x * -1, 0, dRotateX, 0}, {0, 0, 0, 1}};
        mat4 Rtx = {{1, 0, 0, 0}, {0, angletoRotateXhelper, angleToRotateXhelper2, 0}, {0, angleToRotateXhelper2 * -1, angletoRotateXhelper, 0}, {0, 0, 0, 1}};
        
        // multiply all of them together with translation matrix
        mat4 second = m4m4_multiplication(nRtx, nRty);
        mat4 third = m4m4_multiplication(second, Rtz);
        mat4 fourth = m4m4_multiplication(third, Rty);
        mat4 fifth = m4m4_multiplication(fourth, Rtx);
        mat4 final = m4m4_multiplication(fifth, tr_matrix);
        tr_matrix = final;
        printMatrix(final);
        
        
        // This is the brute force method, no multiplicaiton required
        // In this method, we just take the final rotation matrix, and do
        // all the necessary calculations. Tested it and it works perfectly.
        
        //testAngle = 45;
        
//        mat4 rotationMatrix =
//            {{1.0, 0.0, 0.0, 0.0},
//            {0.0, 1.0, 0.0, 0.0},
//            {0.0, 0.0, 1.0, 0.0},
//            {0.0, 0.0, 0.0, 1.0}};
//        
//        rotationMatrix.x.x = cos(testAngle) + aTimesC.x * aTimesC.x * (1 - cos(testAngle));
//        rotationMatrix.x.y = aTimesC.y * aTimesC.x * (1 - cos(testAngle)) + aTimesC.z * sin(testAngle);
//        rotationMatrix.x.z = aTimesC.z * aTimesC.x * (1 - cos(testAngle)) - aTimesC.y * sin(testAngle);
//        rotationMatrix.x.w = 0;
//        
//        rotationMatrix.y.x = aTimesC.x * aTimesC.y * (1 - cos(testAngle)) - aTimesC.z * sin(testAngle);
//        rotationMatrix.y.y = cos(testAngle) + aTimesC.y * aTimesC.y * (1 - cos(testAngle));
//        rotationMatrix.y.z = aTimesC.z * aTimesC.y * (1 - cos(testAngle)) + aTimesC.x * sin(testAngle);
//        rotationMatrix.y.w = 0;
//        
//        rotationMatrix.z.x = aTimesC.x * aTimesC.z * (1 - cos(testAngle)) + aTimesC.y * sin(testAngle);
//        rotationMatrix.z.y = aTimesC.y * aTimesC.z * (1 - cos(testAngle)) - aTimesC.x * sin(testAngle);
//        rotationMatrix.z.z = cos(testAngle) + aTimesC.z * aTimesC.z * (1 - cos(testAngle));
//        rotationMatrix.z.w = 0;
//        
//        rotationMatrix.w.x = 0;
//        rotationMatrix.w.y = 0;
//        rotationMatrix.w.z = 0;
//        rotationMatrix.w.w = 1;
//        
//        testAngle = -45;
//        
//        mat4 rotationMatrix2 =
//        {{1.0, 0.0, 0.0, 0.0},
//            {0.0, 1.0, 0.0, 0.0},
//            {0.0, 0.0, 1.0, 0.0},
//            {0.0, 0.0, 0.0, 1.0}};
//        
//        rotationMatrix2.x.x = cos(testAngle) + aTimesC.x * aTimesC.x * (1 - cos(testAngle));
//        rotationMatrix2.x.y = aTimesC.y * aTimesC.x * (1 - cos(testAngle)) + aTimesC.z * sin(testAngle);
//        rotationMatrix2.x.z = aTimesC.z * aTimesC.x * (1 - cos(testAngle)) - aTimesC.y * sin(testAngle);
//        rotationMatrix2.x.w = 0;
//        
//        rotationMatrix2.y.x = aTimesC.x * aTimesC.y * (1 - cos(testAngle)) - aTimesC.z * sin(testAngle);
//        rotationMatrix2.y.y = cos(testAngle) + aTimesC.y * aTimesC.y * (1 - cos(testAngle));
//        rotationMatrix2.y.z = aTimesC.z * aTimesC.y * (1 - cos(testAngle)) + aTimesC.x * sin(testAngle);
//        rotationMatrix2.y.w = 0;
//        
//        rotationMatrix2.z.x = aTimesC.x * aTimesC.z * (1 - cos(testAngle)) + aTimesC.y * sin(testAngle);
//        rotationMatrix2.z.y = aTimesC.y * aTimesC.z * (1 - cos(testAngle)) - aTimesC.x * sin(testAngle);
//        rotationMatrix2.z.z = cos(testAngle) + aTimesC.z * aTimesC.z * (1 - cos(testAngle));
//        rotationMatrix2.z.w = 0;
//        
//        rotationMatrix2.w.x = 0;
//        rotationMatrix2.w.y = 0;
//        rotationMatrix2.w.z = 0;
//        rotationMatrix2.w.w = 1;
        
        
        //printMatrix(rotationMatrix);
        //printf("newLine \n");
        
        //tr_matrix = m4_transpose(tr_matrix);
        //printf("before \n");
        //printMatrix(rotationMatrix);
        //tr_matrix = m4m4_multiplication(rotationMatrix, tr_matrix);
        //printf("after \n");
        //printMatrix(tr_matrix);
        //printMatrix(rotationMatrix);
        //printf("%f %f %f\n", aTimesC.x, aTimesC.y, aTimesC.z);
        //tr_matrix = final;
        
    }
    glutPostRedisplay();

}



void mouse(int button, int state, int x, int y) {

    float tempx, tempy;
    tempx = (x - 256) / 256.0;
    tempy = (y - 256) / -256.0;
    

    float z = 0.0;
    float sq = 1.0 - (tempx * tempx) - (tempy * tempy);

    if (sq < 0.0) {
        sq = sq * -1;
        z = sqrtf(sq); // initializes the value of coordinate z
        z = z * -1;
    }
    else {
        z = sqrt(sq); // initializes the value of coordinate z
    }
    
    //printf("initialX: %f, initialY: %f, initialZ: %f \n", tempx, tempy, z);

    //printf("%f %f %f sq: %f\n", tempx, tempy, z, sq);
    
    // test coordinates for debugging
//    tempx = 0;
//    tempy = 0;
//    z = 1;
    
    lastx = tempx;
    lasty = tempy;
    lastz = z;
    
    //printf("x: %f, y: %f, z: %f \n", x, y, z);
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        left_button_state = 1; // left button is pressed
    }
    else {
        left_button_state = 0; // left button is released
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Triangle");
   // glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
