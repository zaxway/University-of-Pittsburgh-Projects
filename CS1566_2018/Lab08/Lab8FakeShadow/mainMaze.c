//
//  mainMaze.c
//  MazeProject
//
//  Created by Mohit Jain on 10/24/17.
//  Copyright © 2017 Mohit Jain. All rights reserved.
//

#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include "genMaze.h"

//#else // non-Mac OS X operating systems
//
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include "initShader.h"
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



vec4 cube_vertices[36] =
// front of the cube
{{ -0.5,  0.5,  0.0, 1.0},	// top1
    {-0.5, -0.5,  0.0, 1.0},	// bottom left1
    { 0.5, -0.5,  0.0, 1.0},	// bottom right1
    
    { -0.5,  0.5, 0.0, 1.0},	// top1
    {0.5, 0.5, 0.0, 1.0}, // top2
    {0.5, -0.5, 0.0, 1.0}, // bottom right1
    
    // top of the cube
    {-0.5, 0.5, 0.0, 1.0}, // top1
    {-0.5, 0.5, -1, 1.0}, // backtop1 change y to 0.5 after testing
    {0.5, 0.5, 0.0, 1.0}, // top2
    
    {-0.5, 0.5, -1, 1.0}, // backtop1 change y to 0.5 after testing
    {0.5, 0.5, 0.0, 1.0}, // top2
    {0.5, 0.5, -1, 1.0}, // backtop2 change y to 0.5 after testing
    
    // right side of the cube
    {0.5,-0.5,0, 1.0}, // bottom right1
    {0.5, 0.5, 0, 1}, // top2
    {0.5, -0.5, -1, 1}, // backbottom1 x to 0.5
    
    {0.5, -0.5, -1, 1}, // backbottom1 x to 0.5
    {0.5, 0.5, 0, 1}, // top2
    {0.5, 0.5, -1, 1}, // backtop2 x to 0.5
    
    // left side of the cube
    { -0.5,  0.5,  0.0, 1},	// top1
    {-0.5, -0.5,  0.0, 1},	// bottom left1
    {-0.5, -0.5, -1, 1}, // backbottom2 x to -0.5 left side
    
    { -0.5,  0.5,  0.0, 1},	// top1
    {-0.5, -0.5, -1, 1}, // backbottom2 x to -0.5 left side
    {-0.5, 0.5, -1, 1}, // backtop3 x to -0.5 left side
    
    //bottom of the cube
    {-0.5, -0.5, -1, 1}, // backbottom2 x to -0.5 left side
    {-0.5, -0.5,  0.0, 1},	// bottom left1
    { 0.5, -0.5,  0.0, 1},	// bottom right1
    
    { 0.5, -0.5,  0.0, 1},	// bottom right1
    {-0.5, -0.5, -1, 1}, // backbottom2 x to -0.5 left side
    {0.5, -0.5, -1, 1}, // backbottom1 x to 0.5
    
    //back of the cube
    {0.5, -0.5, -1, 1}, // backbottom1
    {-0.5, -0.5, -1, 1}, //backbottom2
    {-0.5, 0.5, -1, 1}, //backtop1
    
    {-0.5,0.5,-1, 1}, // backtop1
    {0.5, -0.5, -1, 1}, //backbottom1
    {0.5, 0.5, -1, 1}}; //backtop2

vec4 cube_colors[36] =
// front of the cube
{   {1.0, 0, 0.0, 1.0},
    {1.0, 0, 0.0, 1.0},
    {1.0, 0, 0.0, 1.0},
    
    {1.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 1.0},
    
    // top of the cube
    {0.0, 0, 1, 1.0},
    {0.0, 0, 1.0, 1.0},
    {0.0, 0, 1.0, 1.0}, // end of 3
    
    {0.0, 0, 1.0, 1.0},
    {0.0, 0, 1.0, 1.0},
    {0.0, 0, 1.0, 1.0}, //end of 3
    
    //right side of the cube
    {1.0, 1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0, 1.0}, // end of 3
    
    {1.0, 1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0, 1.0}, //end of 3
    
    // left side of the cube
    {1.0, 0.5, 0.0, 1.0},
    {1.0, 0.5, 0.0, 1.0},
    {1.0, 0.5, 0.0, 1.0}, // end of 3
    
    {1.0, 0.5, 0.0, 1.0},
    {1.0, 0.5, 0.0, 1.0},
    {1.0, 0.5, 0.0, 1.0}, //end of 3
    
    
    // bottom of the cube
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0}, // end of 3
    
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0}, // end of 3
    
    // back of the cube
    {0.0, 1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0, 1.0}, // end of 3
    
    {0.0, 1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0, 1.0}}; //end of 3

vec4 pillar_colors[36] =
// front of the cube
{   {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    
    // top of the cube
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, //end of 3
    
    //right side of the cube
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, // end of 3
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, //end of 3
    
    // left side of the cube
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, // end of 3
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, //end of 3
    
    
    // bottom of the cube
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, // end of 3
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, // end of 3
    
    // back of the cube
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}, // end of 3
    
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0},
    {128, 128, 128, 1.0}}; //end of 3

vec4 green_cube_colors[36] =
// front of the cube
{   {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    
    // top of the cube
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    
    //right side of the cube
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    
    // left side of the cube
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    
    // bottom of the cube
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    
    // back of the cube
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    {0, 1, 0.0, 1.0},
    
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0},
    {0, 1.0, 0.0, 1.0}};


GLuint ctm_location;
GLuint proj_matrix;
GLuint model_matrix;

mat4 tr_matrix =
{{1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}};

mat4 temp_tr_cube =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {0.5, 0.25, 0, 1}};

mat4 temp_tr2_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {-0.5, 0.25, 0, 1}};

mat4 scaling_matrix =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {0, 0, 0, 1}};

int enableIdle = 0;
int leftDown = 1;
int i, j, k, v_index = 0;
int num_vertices = 0;
vec4 vertices[232556];
vec4 colors[232556];
vec4 sphere_vertices[116242];
vec4 shadow_cube_vertices[36];

float rotateAngle = 0;
float phi = 0;
int startTestingMazeSolution = 0;

vec4 atp = {0, 0, 0, 1}; // eyePoint past
vec4 eyep = {0, 0.1, 0.1, 1}; // atPoint past
vec4 upv = {0, 1, 0, 1};
vec4 lightSource = {0, 1, 0, 1};



mat4 m4m4_multiplication(mat4 lm, mat4 rm);
vec4 multiplyByScalarVec(vec4 u, float absu);

mat4 matrix_transpose(mat4 lm){
    mat4 result = {{lm.x.x,lm.y.x,lm.z.x,lm.w.x},
        {lm.x.y,lm.y.y,lm.z.y,lm.w.y},
        {lm.x.z,lm.y.z,lm.z.z,lm.w.z},
        {lm.x.w,lm.y.w,lm.z.w,lm.w.w}};
    return result;
}

mat4 multiplyByScalerF(float s, mat4 lm){
    
    mat4 result;
    
    result.x.x = lm.x.x * s;
    result.x.y = lm.x.y * s;
    result.x.z = lm.x.z * s;
    result.x.w = lm.x.w * s;
    
    result.y.x = lm.y.x * s;
    result.y.y = lm.y.y * s;
    result.y.z = lm.y.z * s;
    result.y.w = lm.y.w * s;
    
    result.z.x = lm.z.x * s;
    result.z.y = lm.z.y * s;
    result.z.z = lm.z.z * s;
    result.z.w = lm.z.w * s;
    
    result.w.x = lm.w.x * s;
    result.w.y = lm.w.y * s;
    result.w.z = lm.w.z * s;
    result.w.w = lm.w.w * s;
    
    return result;
}

mat4 matrix_minor(mat4 lm){
    mat4 result;
	   
    result.x.x = (lm.y.y*lm.z.z*lm.w.w) + (lm.z.y*lm.w.z*lm.y.w) + (lm.w.y*lm.y.z*lm.z.w) - (lm.y.w*lm.z.z*lm.w.y) - (lm.z.w*lm.w.z*lm.y.y) - (lm.w.w*lm.y.z*lm.z.y);
    result.x.y = (lm.y.x*lm.z.z*lm.w.w) + (lm.z.x*lm.w.z*lm.y.w) + (lm.w.x*lm.y.z*lm.z.w) - (lm.y.w*lm.z.z*lm.w.x) - (lm.z.w*lm.w.z*lm.y.x) - (lm.w.w*lm.y.z*lm.z.x);
    result.x.z = (lm.y.x*lm.z.y*lm.w.w) + (lm.z.x*lm.w.y*lm.y.w) + (lm.w.x*lm.y.y*lm.z.w) - (lm.y.w*lm.z.y*lm.w.x) - (lm.z.w*lm.w.y*lm.y.x) - (lm.w.w*lm.y.y*lm.z.x);
    result.x.w = (lm.y.x*lm.z.y*lm.w.z) + (lm.z.x*lm.w.y*lm.y.z) + (lm.w.x*lm.y.y*lm.z.z) - (lm.y.z*lm.z.y*lm.w.x) - (lm.z.z*lm.w.y*lm.y.x) - (lm.w.z*lm.y.y*lm.z.x);
    
    result.y.x = (lm.x.y*lm.z.z*lm.w.w) + (lm.z.y*lm.w.z*lm.x.w) + (lm.w.y*lm.x.z*lm.z.w) - (lm.x.w*lm.z.z*lm.w.y) - (lm.z.w*lm.w.z*lm.x.y) - (lm.w.w*lm.x.z*lm.z.y);
    result.y.y = (lm.x.x*lm.z.z*lm.w.w) + (lm.z.x*lm.w.z*lm.x.w) + (lm.w.x*lm.x.z*lm.z.w) - (lm.x.w*lm.z.z*lm.w.x) - (lm.z.w*lm.w.z*lm.x.x) - (lm.w.w*lm.x.z*lm.z.x);
    result.y.z = (lm.x.x*lm.z.y*lm.w.w) + (lm.z.x*lm.w.y*lm.x.w) + (lm.w.x*lm.x.y*lm.z.w) - (lm.x.w*lm.z.y*lm.w.x) - (lm.z.w*lm.w.y*lm.x.x) - (lm.w.w*lm.x.y*lm.z.x);
    result.y.w = (lm.x.x*lm.z.y*lm.w.z) + (lm.z.x*lm.w.y*lm.x.z) + (lm.w.x*lm.x.y*lm.z.z) - (lm.x.z*lm.z.y*lm.w.x) - (lm.z.z*lm.w.y*lm.x.x) - (lm.w.z*lm.x.y*lm.z.x);
    
    result.z.x = (lm.x.y*lm.y.z*lm.w.w) + (lm.y.y*lm.w.z*lm.x.w) + (lm.w.y*lm.x.z*lm.y.w) - (lm.x.w*lm.y.z*lm.w.y) - (lm.y.w*lm.w.z*lm.x.y) - (lm.w.w*lm.x.z*lm.y.y);
    result.z.y = (lm.x.x*lm.y.z*lm.w.w) + (lm.y.x*lm.w.z*lm.x.w) + (lm.w.x*lm.x.z*lm.y.w) - (lm.x.w*lm.y.z*lm.w.x) - (lm.y.w*lm.w.z*lm.x.x) - (lm.w.w*lm.x.z*lm.y.x);
    result.z.z = (lm.x.x*lm.y.y*lm.w.w) + (lm.y.x*lm.w.y*lm.x.w) + (lm.w.x*lm.x.y*lm.y.w) - (lm.x.w*lm.y.y*lm.w.x) - (lm.y.w*lm.w.y*lm.x.x) - (lm.w.w*lm.x.y*lm.y.x);
    result.z.w = (lm.x.x*lm.y.y*lm.w.z) + (lm.y.x*lm.w.y*lm.x.z) + (lm.w.x*lm.x.y*lm.y.z) - (lm.x.z*lm.y.y*lm.w.x) - (lm.y.z*lm.w.y*lm.x.x) - (lm.w.z*lm.x.y*lm.y.x);
    
    result.w.x = (lm.x.y*lm.y.z*lm.z.w) + (lm.y.y*lm.z.z*lm.x.w) + (lm.z.y*lm.x.z*lm.y.w) - (lm.x.w*lm.y.z*lm.z.y) - (lm.y.w*lm.z.z*lm.x.y) - (lm.z.w*lm.x.z*lm.y.y);
    result.w.y = (lm.x.x*lm.y.z*lm.z.w) + (lm.y.x*lm.z.z*lm.x.w) + (lm.z.x*lm.x.z*lm.y.w) - (lm.x.w*lm.y.z*lm.z.x) - (lm.y.w*lm.z.z*lm.x.x) - (lm.z.w*lm.x.z*lm.y.x);
    result.w.z = (lm.x.x*lm.y.y*lm.z.w) + (lm.y.x*lm.z.y*lm.x.w) + (lm.z.x*lm.x.y*lm.y.w) - (lm.x.w*lm.y.y*lm.z.x) - (lm.y.w*lm.z.y*lm.x.x) - (lm.z.w*lm.x.y*lm.y.x);
    result.w.w = (lm.x.x*lm.y.y*lm.z.z) + (lm.y.x*lm.z.y*lm.x.z) + (lm.z.x*lm.x.y*lm.y.z) - (lm.x.z*lm.y.y*lm.z.x) - (lm.y.z*lm.z.y*lm.x.x) - (lm.z.z*lm.x.y*lm.y.x);
    return result;
}

mat4 matrix_cofactor(mat4 lm){
    mat4 result;
    
    result.x.x = lm.x.x;
    result.x.y = lm.x.y*-1;
    result.x.z = lm.x.z;
    result.x.w = lm.x.w*-1;
    
    result.y.x = lm.y.x*-1;
    result.y.y = lm.y.y;
    result.y.z = lm.y.z*-1;
    result.y.w = lm.y.w;
    
    result.z.x = lm.z.x;
    result.z.y = lm.z.y*-1;
    result.z.z = lm.z.z;
    result.z.w = lm.z.w*-1;
    
    result.w.x = lm.w.x*-1;
    result.w.y = lm.w.y;
    result.w.z = lm.w.z*-1;
    result.w.w = lm.w.w;
    
    return result;
}

float matrix_determinant(mat4 lm){
    mat4 minor = matrix_minor(lm);
    float determ = (lm.x.x*minor.x.x) - (lm.x.y*minor.x.y) + (lm.x.z*minor.x.z) - (lm.x.w*minor.x.w);
    return determ;
}

mat4 matrix_inverse(mat4 lm){
    mat4 minor = matrix_minor(lm);
    //mat4_print(minor);
    mat4 cofactor = matrix_cofactor(minor);
    //mat4_print(cofactor);
    mat4 transpose = matrix_transpose(cofactor);
    float determinant = matrix_determinant(lm);
    if(determinant!=0){
        mat4 lm_inv = multiplyByScalerF(1/determinant, transpose);
        return(lm_inv);
    }
    else{
        return lm;
    }
    
}

vec4 m4v4_multiplication(mat4 m, vec4 v) {
    float x = m.x.x * v.x + m.y.x * v.y + m.z.x * v.z + m.w.x * v.w;
    float y = m.x.y * v.x + m.y.y * v.y + m.z.y * v.z + m.w.y * v.w;
    float z = m.x.z * v.x + m.y.z * v.y + m.z.z * v.z + m.w.z * v.w;
    float w = m.x.w * v.x + m.y.w * v.y + m.z.w * v.z + m.w.w * v.w;
    vec4 result = {x, y, z, w};
    return result;
}

vec4 v4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    vec4 result = {x, y, z, w};
    return result;
}

mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    mat4 result = {{1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}};
    result.w.x = x;
    result.w.y = y;
    result.w.z = z;
    return result;
}

vec4 *maze(int *num_vertices)
{
    *num_vertices = 232556;
    vec4 *vertices = (vec4 *) malloc (sizeof(vec4) * 232556);
    float xShadow = 0;
    float zShadow = 0;
    float zShadowHelp = 0;
    float xShadowHelp = 0;
    
    for (i = 0; i < 36; i++) {
        vertices[v_index] = m4v4_multiplication(temp_tr_cube, cube_vertices[i]);
        shadow_cube_vertices[i] = v4(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z, 1);
        colors[v_index] = cube_colors[i];
        v_index++;
    }
    
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_tr2_sphere, vertices[v_index]);
            // updates sphere_vertices used for shadowing
            sphere_vertices[i] = v4(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z, 1);
            // colors actual sphere
            colors[v_index] = v4(1, 0, 0, 1);
            
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_tr2_sphere, vertices[v_index]);
            sphere_vertices[i] = v4(vertices[v_index].x, vertices[v_index].y, vertices[v_index].z, 1);
            colors[v_index] = v4(1, 0, 0, 1);
            
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    // this will fill in the shadow for the sphere
    // starts at vertex 116278
    printf("%d \n", v_index);
    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - sphere_vertices[j].x) / (lightSource.y - sphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - sphere_vertices[j].z) / (lightSource.y - sphere_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);
    }
    
    // this will fill in the shadow for the cube.
    // starts at vertex 232520
    printf("%d \n", v_index);
    for (j = 0; j < 36; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - shadow_cube_vertices[j].x) / (lightSource.y - shadow_cube_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - shadow_cube_vertices[j].z) / (lightSource.y - shadow_cube_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);

    }
    
    
    return vertices;
}


void init(void)
{
    GLuint program = initShader("/Users/mohitjain/Documents/CS1566_2018/Lab8FakeShadow/Lab8FakeShadow/vshader.glsl", "/Users/mohitjain/Documents/CS1566_2018/Lab8FakeShadow/Lab8FakeShadow/fshader.glsl");
    glUseProgram(program);
    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
    
    int maze_num_vertices;
    vec4 *maze_vertices = maze(&maze_num_vertices);
    num_vertices = maze_num_vertices;
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * 2 * num_vertices, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * num_vertices, maze_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices, sizeof(vec4) * num_vertices, colors);
    
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    
    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices));
    
    model_matrix = glGetUniformLocation(program, "model_view_matrix");
    
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glDepthRange(1,0);
}

vec4 crossProduct(vec4 u, vec4 v) {
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
    vec4 result = {(uvi), (uvj), (uvk), 1};
    return result;
    
}

vec4 subtractVector(vec4 u, vec4 v) {
    vec4 result = {(u.x - v.x), (u.y - v.y), (u.z - v.z), (u.w - v.w)};
    return result;
}

vec4 normalize(vec4 u) {
    float finalLength = 0.0;
    float sqlength = (u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.w * u.w);
    finalLength = sqrtf(sqlength);
    float ilen = 1.0 / finalLength;
    vec4 rslt = {u.x * ilen, u.y * ilen, u.z * ilen, u.w * ilen};
    return rslt;
}

vec3 v3v3_addition(vec3 v1, vec3 v2)
{
    vec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

vec4 multiplyByScalarVec(vec4 u, float absu) {
    vec4 result = {(u.x * absu), (u.y * absu), (u.z * absu), (u.w * absu)};
    return result;
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
    
    return result;
}

void printMatrix(mat4 m) {
    printf("%f %f %f %f \n", m.x.x, m.y.x, m.z.x, m.w.x);
    printf("%f %f %f %f \n", m.x.y, m.y.y, m.z.y, m.w.y);
    printf("%f %f %f %f \n", m.x.z, m.y.z, m.z.z, m.w.z);
    printf("%f %f %f %f \n", m.x.w, m.y.w, m.z.w, m.w.w);
    
}

float dotProduct(vec4 u, vec4 v)
{
    
    float product = 0.0;
    
    // Loop for calculate cot product
    float productCalc1 = u.x * v.x;
    float productCalc2 = u.y * v.y;
    float productCalc3 = u.z * v.z;
    product = productCalc1 + productCalc2 + productCalc3;
    return product;
}

vec4 v4v4_multiplication(vec4 u, vec4 v) {
    vec4 result;
    result.x = u.x * v.x;
    result.y = u.y * v.y;
    result.z = u.z * v.z;
    result.w = u.w * v.w;
    return result;
}

vec4 v4v4_sub(vec4 a,vec4 b){
    vec4 result;
    
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    
    return(result);
}

vec4 v4_scalarMult(float s,vec4 input){
    
    vec4 result;
    
    result.x = s * input.x;
    result.y = s * input.y;
    result.z = s * input.z;
    result.w = s * input.w;
    
    return(result);
}


mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVector) {
    mat4 result = {{1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}};
    
    
    vec4 sub = subtractVector(atPoint, eyePoint);
    vec4 n = normalize(sub);
    
    vec4 yaxisHelp = crossProduct(n, upVector);
    vec4 u = normalize(yaxisHelp);
    
    vec4 v = crossProduct(u, n);
    
    result.x.x = u.x;
    result.x.y = v.x;
    result.x.z = n.x * -1;
    result.x.w = 0;
    
    result.y.x = u.y;
    result.y.y = v.y;
    result.y.z = n.y * -1;
    result.y.w = 0;
    
    result.z.x = u.z;
    result.z.y = v.z;
    result.z.z = n.z * -1;
    result.z.w = 0;
    result.w.w = 1;

    
    return m4m4_multiplication(result, translate(eyePoint.x, eyePoint.y, eyePoint.z));
}

mat4 frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top,
             GLfloat near, GLfloat far) {
    
    mat4 result = {{1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}};
    
    result.x.x = (2 * near) / (right - left);
    result.y.y = (2 * near) / (top - bottom);
    result.z.x = (right + left) / (right - left);
    result.z.y = (top + bottom) / (top - bottom);
    result.z.z = -1 * (far + near) / (far - near);
    result.z.w = -1;
    result.w.x = 0;
    result.w.y = 0;
    result.w.z = (-2 * far * near) / (far - near);
    return result;

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    printf("eyep: %f %f %f \n", eyep.x, eyep.y, eyep.z);
    printf("______________ \n");
    mat4 mv = look_at(eyep, atp, upv); // switched up curr
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, (GLfloat *) &mv);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawArrays(GL_TRIANGLES, 36, 116242);
    glDrawArrays(GL_TRIANGLES, 116278, 116242);
    glDrawArrays(GL_TRIANGLES, 232521, 35);
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
        exit(0);
    
    if(!enableIdle)
    {
        if(key == 'X')
            eyep.z += 0.5;
        else if(key == 'x') {
            rotateAngle += 1;
            phi += 1;
            //eyep.x = 5.315 * cos(rotateAngle * M_PI/180);
            //eyep.y = 5.315 * sin(rotateAngle * M_PI/180) * cos(phi * M_PI/180);
            //eyep.z = 5.315 * sin(rotateAngle * M_PI/180) * sin(phi * M_PI/180);
            
//            eyep = m4v4_multiplication(m, eyep);
        }
        else if(key == 'Y')
            eyep.y += 0.5;
        else if(key == 'y')
            eyep.y -= 0.5;
        else if(key == 'z') {
            eyep.z -= 0.5;
            if (eyep.z == -7.5 && startTestingMazeSolution == 1) {
                atp.x = 1;
                atp.y = 0;
                atp.z = -7.5;
            }
        }
        else if(key == 'Z') {
            eyep.z += 0.5;
        }
        else if(key == 'F')
            eyep.x += 0.5;
        else if (key == 'f') {
            eyep.x -= 0.5;
            if (eyep.x == -1 && startTestingMazeSolution == 1) {
                atp.x = -1;
                atp.y = 0;
                atp.z = -2.5;
            }

        }
        else if(key == ' ')
        {
            enableIdle = 1;
        }
        
        glutPostRedisplay();
    }
    else
    {
        if(key == ' ')
        {
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
            atp.x = 0;
            atp.y = 0;
            atp.z = 1;
            eyep.x = 0;
            eyep.y = 0.5;
            eyep.z = -1;
            startTestingMazeSolution = 1;
        }
        
        glutPostRedisplay();
    }
}


void motion(int x, int y) {

}



void mouse(int button, int state, int x, int y) {

}

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("MazeProject");
    // glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    //glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return 0;
}
