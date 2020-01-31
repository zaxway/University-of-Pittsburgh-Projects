/*
 * Project 1
 *
 *  Created on: 10/12/18
 *      Author: Mohit Jain
 */


#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

#endif  // __APPLE__

#include "initShader.h"
#include <time.h>

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
    
    return vertices;
}

vec4 *genRandomTriangleColors(int num_vertices)
{
    GLfloat r, g, b;
    int index = 0, i;
    
    srand(time(0));
    
    vec4 *colors = (vec4 *) malloc(sizeof(vec4) * num_vertices);
    float theta, theta_r, theta10_r;
    
    // Sphere code
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            colors[index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            index = index + 1;
            colors[index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            index = index + 1;
        }
    }

    
    return colors;
}


void init(void)
{
    GLuint program = initShader("/Users/mohitjain/Documents/Fall2017/CS1566/Projects/Project1/triangle2s/vshader.glsl", "/Users/mohitjain/Documents/Fall2017/CS1566/Projects/Project1/triangle2s/fshader.glsl");
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
    
    ctm_location = glGetUniformLocation(program, "ctm");
    
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
    finalLength = sqrtf(sqlength);
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

mat4 m4m4_multiplication(mat4 a, mat4 b) {
    mat4 result;
    
    result.x.x = (a.x.x * b.x.x) + (a.y.x * b.x.y) + (a.z.x * b.x.z) + (a.w.x * b.x.w);
    result.x.y = (a.x.y * b.x.x) + (a.y.y * b.x.y) + (a.z.y * b.x.z) + (a.w.y * b.x.w);
    result.x.z = (a.x.z * b.x.x) + (a.y.z * b.x.y) + (a.z.z * b.x.z) + (a.w.z * b.x.w);
    result.x.w = (a.x.w * b.x.x) + (a.y.w * b.x.y) + (a.z.w * b.x.z) + (a.w.w * b.x.w);
    
    result.y.x = (a.x.x * b.y.x) + (a.y.x * b.y.y) + (a.z.x * b.y.z) + (a.w.x * b.y.w);
    result.y.y = (a.x.y * b.y.x) + (a.y.y * b.y.y) + (a.z.y * b.y.z) + (a.w.y * b.y.w);
    result.y.z = (a.x.z * b.y.x) + (a.y.z * b.y.y) + (a.z.z * b.y.z) + (a.w.z * b.y.w);
    result.y.w = (a.x.w * b.y.x) + (a.y.w * b.y.y) + (a.z.w * b.y.z) + (a.w.w * b.y.w);
    
    result.z.x = (a.x.x * b.z.x) + (a.y.x * b.z.y) + (a.z.x * b.z.z) + (a.w.x * b.z.w);
    result.z.y = (a.x.y * b.z.x) + (a.y.y * b.z.y) + (a.z.y * b.z.z) + (a.w.y * b.z.w);
    result.z.z = (a.x.z * b.z.x) + (a.y.z * b.z.y) + (a.z.z * b.z.z) + (a.w.z * b.z.w);
    result.z.w = (a.x.w * b.z.x) + (a.y.w * b.z.y) + (a.z.w * b.z.z) + (a.w.w * b.z.w);
    
    result.w.x = (a.x.x * b.w.x) + (a.y.x * b.w.y) + (a.z.x * b.w.z) + (a.w.x * b.w.w);
    result.w.y = (a.x.y * b.w.x) + (a.y.y * b.w.y) + (a.z.y * b.w.z) + (a.w.y * b.w.w);
    result.w.z = (a.x.z * b.w.x) + (a.y.z * b.w.y) + (a.z.z * b.w.z) + (a.w.z * b.w.w);
    result.w.w = (a.x.w * b.w.x) + (a.y.w * b.w.y) + (a.z.w * b.w.z) + (a.w.w * b.w.w);
    
    return(result);
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
            tr_matrix = m4m4_multiplication(scaling_matrix, tr_matrix);
            printf("%f %f %f %f\n", tr_matrix.x.x, tr_matrix.y.x, tr_matrix.z.x, tr_matrix.w.x);
            glutPostRedisplay();
        }
        else if (key == 'l') {
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
        z = sqrtf(sq); // initializes the value of coordinate z
    }
    // test coordinates for debugging
//    tempx = 12;
//    tempy = 8;
//    z = 0;
//    float testAngle = 60.0;
    
    
    if (left_button_state == 1) {
        
        vec3 atPointA = {(lastx),(lasty),(lastz)};
        vec3 atPointC = {(tempx), (tempy), (z)};
        printf("lastx: %f \n", lastx);
        printf("tempx: %f \n", tempx);
        
        vec3 aMinusC = crossProduct(atPointC, atPointA);
        if (aMinusC.x == 0 && aMinusC.y == 0 && aMinusC.z == 0) {
            return;
        }
        float lengthOfaMinusC = lengthOfVector(aMinusC);
        if (lengthOfaMinusC == 0 || lengthOfaMinusC < 0) {
            lengthOfaMinusC = 0.01;
        }
        // vector of rotation
        vec4 aTimesC = {(aMinusC.x / lengthOfaMinusC), (aMinusC.y / lengthOfaMinusC), (aMinusC.z / lengthOfaMinusC), 0.0};
        //printf("vecX: %f, vecY: %f, vecZ: %f \n", aTimesC.x, aTimesC.y, aTimesC.z);
        
        // rotate to y = 0
        float dRotateXhelper = (aTimesC.y * aTimesC.y) + (aTimesC.z * aTimesC.z);
        float dRotateX = sqrtf(dRotateXhelper); // this is d
        if (dRotateX == 0) {
            dRotateX = 1;
        }
        
        float angletoRotateXhelper = aTimesC.z / dRotateX; // z / d
        //printf("angleX1: %f \n", angletoRotateXhelper);
        float angleToRotateXhelper2 = aTimesC.y / dRotateX; // y / d
        //printf("angleX2: %f \n", angleToRotateXhelper2);
        
        // this is for rotation of z
        float dotProd = dotProduct(atPointA, atPointC);
        //printf("dotProd: %f \n", dotProd);
        if (dotProd > 1) {
            dotProd = 0.9999;
        }
        else if (dotProd < -1) {
            dotProd = -0.9999;
        }
        float testAngle = acos(dotProd);
        //printf("testAngle: %f \n", testAngle);
        
        // now move the sphere by doing all the necessary calculations
        // get all matrices
        mat4 nRtx = {{1, 0, 0, 0}, {0, angletoRotateXhelper, angleToRotateXhelper2 * -1, 0}, {0, angleToRotateXhelper2, angletoRotateXhelper, 0}, {0, 0, 0, 1}};
        mat4 nRty = {{dRotateX, 0, aTimesC.x, 0}, {0, 1, 0, 0}, {aTimesC.x * -1, 0, dRotateX, 0}, {0, 0, 0, 1}};
        mat4 Rtz = {{cos(testAngle), sin(testAngle), 0, 0}, {sin(testAngle) * -1, cos(testAngle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        mat4 Rty = {{dRotateX, 0, aTimesC.x * -1, 0}, {0, 1, 0, 0}, {aTimesC.x, 0, dRotateX, 0}, {0, 0, 0, 1}};
        mat4 Rtx = {{1, 0, 0, 0}, {0, angletoRotateXhelper, angleToRotateXhelper2, 0}, {0, angleToRotateXhelper2 * -1, angletoRotateXhelper, 0}, {0, 0, 0, 1}};
        
//        mat4 nRtx = {{1, 0, 0, 0}, {0, c/v, b/v * -1, 0}, {0, b/v, c/v, 0}, {0, 0, 0, 1}};
//        mat4 nRty = {{v/l, 0, a/l * -1, 0}, {0, 1, 0, 0}, {a/l, 0, v/l, 0}, {0, 0, 0, 1}};
//        mat4 Rtz = {{cos(testAngle), sin(testAngle), 0, 0}, {sin(testAngle) * -1, cos(testAngle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
//        mat4 Rty = {{v/l, 0, a/l, 0}, {0, 1, 0, 0}, {a/l * -1, 0, v/l, 0}, {0, 0, 0, 1}};
//        mat4 Rtx = {{1, 0, 0, 0}, {0, c/v, b/v, 0}, {0, b/v * -1, c/v, 0}, {0, 0, 0, 1}};
        
        // multiply all of them together with translation matrix
        mat4 second = m4m4_multiplication(nRtx, nRty);
        mat4 third = m4m4_multiplication(second, Rtz);
        mat4 fourth = m4m4_multiplication(third, Rty);
        mat4 fifth = m4m4_multiplication(fourth, Rtx);
        tr_matrix = m4m4_multiplication(fifth, tr_matrix);
        lastx = tempx;
        printf("lastx: %f \n", lastx);
        lasty = tempy;
        lastz = z;
        glutPostRedisplay();
    }

}



void mouse(int button, int state, int x, int y) {
    
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        left_button_state = 1; // left button is pressed
        float tempx, tempy;
        tempx = (x - 256) / 256.0;
        tempy = (y - 256) / -256.0;
        
//
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
        
        // test coordinates for debugging
//            tempx = 6;
//            tempy = -2;
//            z = 0;
        lastx = tempx;
        lasty = tempy;
        lastz = z;

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
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
