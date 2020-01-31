#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

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

void printMatrix(mat4 m);
vec4 v4v4_sub(vec4 a,vec4 b);
vec4 v4_scalarMult(float s,vec4 input);
mat4 frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top,
             GLfloat near, GLfloat far);
vec4 subtractVector(vec4 u, vec4 v);
float magnitude(vec4 u);
GLfloat attenuation(GLfloat d);
mat4 matrix_transpose(mat4 lm);
mat4 multiplyByScalerF(float s, mat4 lm);
mat4 matrix_minor(mat4 lm);
mat4 matrix_cofactor(mat4 lm);
float matrix_determinant(mat4 lm);
mat4 matrix_inverse(mat4 lm);
vec4 m4v4_multiplication(mat4 m, vec4 v);
vec4 v4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
mat4 translate(GLfloat x, GLfloat y, GLfloat z);
vec4 v4v4_addition(vec4 v1, vec4 v2);
vec4 v4v4_multiplication(vec4 u, vec4 v);
vec4 crossProduct(vec4 u, vec4 v);
vec4 normalize(vec4 u);
vec4 multiplyByScalarVec(vec4 u, float absu);
float dotProduct(vec4 u, vec4 v);
void print_vector(vec4 u);
mat4 look_at(vec4 eyePoint, vec4 atPoint, vec4 upVector);


vec4 subtractVector(vec4 u, vec4 v) {
    vec4 result = {(u.x - v.x), (u.y - v.y), (u.z - v.z), (u.w - v.w)};
    return result;
}

float magnitude(vec4 u) {
    float finalLength = 0.0;
    float sqlength = (u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.w * u.w);
    finalLength = sqrtf(sqlength);
    return finalLength;
}

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

vec4 v4v4_addition(vec4 v1, vec4 v2)
{
    vec4 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    result.w = v1.w + v2.w;
    return result;
}

vec4 v4v4_multiplication(vec4 u, vec4 v) {
    vec4 result;
    result.x = u.x * v.x;
    result.y = u.y * v.y;
    result.z = u.z * v.z;
    result.w = u.w * v.w;
    return result;
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

vec4 normalize(vec4 u) {
    float finalLength = 0.0;
    float sqlength = (u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.w * u.w);
    finalLength = sqrtf(sqlength);
    float ilen = 1.0 / finalLength;
    vec4 rslt = {u.x * ilen, u.y * ilen, u.z * ilen, u.w * ilen};
    return rslt;
}

vec4 multiplyByScalarVec(vec4 u, float absu) {
    vec4 result = {(u.x * absu), (u.y * absu), (u.z * absu), (u.w * absu)};
    return result;
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

void print_vector(vec4 u) {
    printf("x: %f, y: %f, z: %f, w: %f \n", u.x, u.y, u.z, u.w);
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

void printMatrix(mat4 m) {
    printf("%f %f %f %f \n", m.x.x, m.y.x, m.z.x, m.w.x);
    printf("%f %f %f %f \n", m.x.y, m.y.y, m.z.y, m.w.y);
    printf("%f %f %f %f \n", m.x.z, m.y.z, m.z.z, m.w.z);
    printf("%f %f %f %f \n", m.x.w, m.y.w, m.z.w, m.w.w);
    
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


