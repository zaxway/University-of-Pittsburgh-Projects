//
//  main.c
//  Project3
//
//  Created by Mohit Jain on 12/7/18.
//  Copyright © 2018 Mohit Jain. All rights reserved.
//

#include "LabAssignment1.c"
#include "initShader.c"
#include "initShader.h"

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

typedef struct
{
    vec4 reflect_ambient;
    vec4 reflect_diffuse;
    vec4 reflect_specular;
    GLfloat shininess;
} material;

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


GLuint ctm_location;
GLuint proj_matrix;
GLuint model_matrix;

GLuint ambient_product_loc;
GLuint diffuse_product_loc;
GLuint specular_product_loc;
GLuint light_position_loc;
GLuint shininess_loc;


mat4 tr_matrix =
{{1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}};

mat4 tr_cube =
{{10.0, 0.0, 0.0, 0.0},
    {0.0, 10.0, 0.0, 0.0},
    {0.0, 0.0, 0.1, 0.0},
    {0.0, 0, 0.0, 1.0}};

mat4 temp_red_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {0, 0.5, 0, 1}};

mat4 temp_green_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {1.0, 0.5, 0, 1}};

mat4 temp_blue_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {2.0, 0.5, 0, 1}};

mat4 temp_yellow_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {3.0, 0.5, 0, 1}};

mat4 temp_orange_sphere =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {4.0, 0.5, 0, 1}};

mat4 scaling_matrix =
{{0.5, 0, 0, 0},
    {0, 0.5, 0, 0},
    {0, 0, 0.5, 0},
    {0, 0, 0, 1}};

int enableIdle = 0;
int leftDown = 1;
int i, j, k, v_index = 0;
int num_vertices = 0;

vec4 vertices[1162456];
vec4 redSphere_vertices[116242];
vec4 greenSphere_vertices[116242];
vec4 blueSphere_vertices[116242];
vec4 yellowSphere_vertices[116242];
vec4 orangeSphere_vertices[116242];

vec4 colors[1162456];
vec4 sphere_vertices[116242];
vec4 shadow_cube_vertices[36];

float rotateAngle = 0;
float phi = 0;

vec4 atp = {0, -0.4, 0, 1};
vec4 eyep = {0, 0.1, 0.1, 1};
vec4 upv = {0, 1, 0, 1};
vec4 lightSource = {0, 3, 0, 0};

vec4 light_diffuse = {1.0, 1.0, 1.0, 1.0};
vec4 light_specular = {1.0, 1.0, 1.0, 1.0};
vec4 light_ambient = {0.2, 0.2, 0.2, 1.0};

vec4 ambient, diffuse, specular;

GLfloat attenuation_constant = 1;
GLfloat attenuation_linear = 2;
GLfloat attenuation_quadratic = 2;

material ball_materials[5] = {
    {{1.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 100},
    {{0.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 100},
    {{0.0, 0.0, 1.0, 1.0}, {0.0, 0.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 100},
    {{1.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 100},
    {{1.0, 0.5, 0.0, 1.0}, {1.0, 0.5, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 100}};

GLfloat attenuation(GLfloat d)
{
    return 1 / (attenuation_constant + (attenuation_linear * d) +
                (attenuation_quadratic * d * d));
}

vec4 *maze(int *num_vertices)
{
    *num_vertices = 1162456;
    vec4 *vertices = (vec4 *) malloc (sizeof(vec4) * 1162456);
    
    float xShadow = 0;
    float zShadow = 0;
    float zShadowHelp = 0;
    float xShadowHelp = 0;
    
    int a = 0;
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_red_sphere, vertices[v_index]);
            //colors[v_index] = v4(1, 0, 0, 1);
            redSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_red_sphere, vertices[v_index]);
            //colors[v_index] = v4(1, 0, 0, 1);
            redSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    //int badTimes = 0;
    for (a = 0; a < 116242; a = a + 3) {
        int m = 0;
        vec4 p0 = vertices[a];
        vec4 p1 = vertices[a + 1];
        vec4 p2 = vertices[a + 2];
        // calculate normal for all three vertices
        p0 = normalize(p0);
        p1 = normalize(p1);
        p2 = normalize(p2);
        
        // calculate ambient, specular, and diffuse
        ambient = v4v4_multiplication(light_ambient, ball_materials[m].reflect_ambient);
        
        vec4 n = normalize(crossProduct(subtractVector(p1, p0), subtractVector(p2, p1)));
        vec4 zeroVec = {0.0, 0.0, 0.0, 1.0};
        // constant shading with distant source
        diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 vector_position = multiplyByScalarVec(v4v4_addition(v4v4_addition(p0, p1), p2), (1.0/3.0));
        vec4 light_vector = subtractVector(lightSource, vector_position);
        diffuse = v4v4_multiplication(light_diffuse, ball_materials[m].reflect_diffuse);
        GLfloat d = dotProduct(n, normalize(light_vector));
        if (d > 0.0) {
            diffuse = multiplyByScalarVec(diffuse, d);
        }
        else {
            diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        }

        specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 view_direction = normalize(subtractVector(vector_position, zeroVec));
        vec4 half = normalize(v4v4_addition(lightSource, view_direction));
        GLfloat s = dotProduct(half, n);
        if (s > 0.0) {
            specular = multiplyByScalarVec(v4v4_multiplication(light_specular, ball_materials[m].reflect_specular), pow(s, ball_materials[m].shininess));
        }
        else {
            //badTimes++;
            specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        float distance = magnitude(subtractVector(lightSource, vector_position));
        float atten = attenuation(distance);
        // calculate color for the first vertex
        colors[a] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a].w = 1.0;
        
        // calculate color for the second vertex
        colors[a + 1] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 1].w = 1.0;
        
        // calculate color for the third vertex
        colors[a + 2] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 2].w = 1.0;
    }
    
    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - redSphere_vertices[j].x) / (lightSource.y - redSphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - redSphere_vertices[j].z) / (lightSource.y - redSphere_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);
    }
    
    // End of Red Sphere
    
    // Start of Green Sphere
    
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_green_sphere, vertices[v_index]);
            //colors[v_index] = v4(0, 1, 0, 1);
            greenSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_green_sphere, vertices[v_index]);
            //colors[v_index] = v4(0, 1, 0, 1);
            greenSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    
    for (a = 232484; a < 348726; a = a + 3) {
        int m = 1;
        vec4 p0 = vertices[a];
        vec4 p1 = vertices[a + 1];
        vec4 p2 = vertices[a + 2];
        // calculate normal for all three vertices
        p0 = normalize(p0);
        p1 = normalize(p1);
        p2 = normalize(p2);
        
        // calculate ambient, specular, and diffuse
        ambient = v4v4_multiplication(light_ambient, ball_materials[m].reflect_ambient);
        
        vec4 n = normalize(crossProduct(subtractVector(p1, p0), subtractVector(p2, p1)));
        vec4 zeroVec = {0.0, 0.0, 0.0, 1.0};
        // constant shading with distant source
        diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 vector_position = multiplyByScalarVec(v4v4_addition(v4v4_addition(p0, p1), p2), (1.0/3.0));
        vec4 light_vector = subtractVector(lightSource, vector_position);
        diffuse = v4v4_multiplication(light_diffuse, ball_materials[m].reflect_diffuse);
        GLfloat d = dotProduct(n, normalize(light_vector));
        if (d > 0.0) {
            diffuse = multiplyByScalarVec(diffuse, d);
        }
        else {
            diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        
        specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 view_direction = normalize(subtractVector(vector_position, zeroVec));
        vec4 half = normalize(v4v4_addition(lightSource, view_direction));
        GLfloat s = dotProduct(half, n);
        if (s > 0.0) {
            specular = multiplyByScalarVec(v4v4_multiplication(light_specular, ball_materials[m].reflect_specular), pow(s, ball_materials[m].shininess));
        }
        else {
            specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        float distance = magnitude(subtractVector(lightSource, vector_position));
        float atten = attenuation(distance);
        // calculate color for the first vertex
        colors[a] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a].w = 1.0;
        
        // calculate color for the second vertex
        colors[a + 1] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 1].w = 1.0;
        
        // calculate color for the third vertex
        colors[a + 2] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 2].w = 1.0;
    }

    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - greenSphere_vertices[j].x) / (lightSource.y - greenSphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - greenSphere_vertices[j].z) / (lightSource.y - greenSphere_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);
    }
    
    // End of Green Sphere
    
    // Start of Blue Sphere
    
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_blue_sphere, vertices[v_index]);
            //colors[v_index] = v4(0, 0, 1, 1);
            blueSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_blue_sphere, vertices[v_index]);
            //colors[v_index] = v4(0, 0, 1, 1);
            blueSphere_vertices[i] = vertices[v_index];
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    
    for (a = 464968; a < 581210; a = a + 3) {
        int m = 2;
        vec4 p0 = vertices[a];
        vec4 p1 = vertices[a + 1];
        vec4 p2 = vertices[a + 2];
        // calculate normal for all three vertices
        p0 = normalize(p0);
        p1 = normalize(p1);
        p2 = normalize(p2);
        
        // calculate ambient, specular, and diffuse
        ambient = v4v4_multiplication(light_ambient, ball_materials[m].reflect_ambient);
        
        vec4 n = normalize(crossProduct(subtractVector(p1, p0), subtractVector(p2, p1)));
        vec4 zeroVec = {0.0, 0.0, 0.0, 1.0};
        // constant shading with distant source
        diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 vector_position = multiplyByScalarVec(v4v4_addition(v4v4_addition(p0, p1), p2), (1.0/3.0));
        vec4 light_vector = subtractVector(lightSource, vector_position);
        diffuse = v4v4_multiplication(light_diffuse, ball_materials[m].reflect_diffuse);
        GLfloat d = dotProduct(n, normalize(light_vector));
        if (d > 0.0) {
            diffuse = multiplyByScalarVec(diffuse, d);
        }
        else {
            diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        
        specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 view_direction = normalize(subtractVector(vector_position, zeroVec));
        vec4 half = normalize(v4v4_addition(lightSource, view_direction));
        GLfloat s = dotProduct(half, n);
        if (s > 0.0) {
            specular = multiplyByScalarVec(v4v4_multiplication(light_specular, ball_materials[m].reflect_specular), pow(s, ball_materials[m].shininess));
        }
        else {
            specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        float distance = magnitude(subtractVector(lightSource, vector_position));
        float atten = attenuation(distance);
        // calculate color for the first vertex
        colors[a] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a].w = 1.0;
        
        // calculate color for the second vertex
        colors[a + 1] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 1].w = 1.0;
        
        // calculate color for the third vertex
        colors[a + 2] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 2].w = 1.0;
    }

    
    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - blueSphere_vertices[j].x) / (lightSource.y - blueSphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - blueSphere_vertices[j].z) / (lightSource.y - blueSphere_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);
    }
    
    // End of Blue Sphere
    
    // Start of Yellow Sphere
    
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_yellow_sphere, vertices[v_index]);
            yellowSphere_vertices[i] = vertices[v_index];
            //colors[v_index] = v4(1, 1, 0, 1);
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_yellow_sphere, vertices[v_index]);
            yellowSphere_vertices[i] = vertices[v_index];
            //colors[v_index] = v4(1, 1, 0, 1);
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    
    for (a = 697452; a < 813694; a = a + 3) {
        int m = 3;
        vec4 p0 = vertices[a];
        vec4 p1 = vertices[a + 1];
        vec4 p2 = vertices[a + 2];
        // calculate normal for all three vertices
        p0 = normalize(p0);
        p1 = normalize(p1);
        p2 = normalize(p2);
        
        // calculate ambient, specular, and diffuse
        ambient = v4v4_multiplication(light_ambient, ball_materials[m].reflect_ambient);
        
        vec4 n = normalize(crossProduct(subtractVector(p1, p0), subtractVector(p2, p1)));
        vec4 zeroVec = {0.0, 0.0, 0.0, 1.0};
        // constant shading with distant source
        diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 vector_position = multiplyByScalarVec(v4v4_addition(v4v4_addition(p0, p1), p2), (1.0/3.0));
        vec4 light_vector = subtractVector(lightSource, vector_position);
        diffuse = v4v4_multiplication(light_diffuse, ball_materials[m].reflect_diffuse);
        GLfloat d = dotProduct(n, normalize(light_vector));
        if (d > 0.0) {
            diffuse = multiplyByScalarVec(diffuse, d);
        }
        else {
            diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        
        specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 view_direction = normalize(subtractVector(vector_position, zeroVec));
        vec4 half = normalize(v4v4_addition(lightSource, view_direction));
        GLfloat s = dotProduct(half, n);
        if (s > 0.0) {
            specular = multiplyByScalarVec(v4v4_multiplication(light_specular, ball_materials[m].reflect_specular), pow(s, ball_materials[m].shininess));
        }
        else {
            specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        float distance = magnitude(subtractVector(lightSource, vector_position));
        float atten = attenuation(distance);
        // calculate color for the first vertex
        colors[a] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a].w = 1.0;
        
        // calculate color for the second vertex
        colors[a + 1] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 1].w = 1.0;
        
        // calculate color for the third vertex
        colors[a + 2] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 2].w = 1.0;
    }
    
    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - yellowSphere_vertices[j].x) / (lightSource.y - yellowSphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - yellowSphere_vertices[j].z) / (lightSource.y - yellowSphere_vertices[j].y));
        zShadow = lightSource.z - zShadowHelp;
        
        // update v_index
        v_index = v_index + 1;
        vertices[v_index] = v4(xShadow, 0, zShadow, 1);
        colors[v_index] = v4(0, 0, 0, 1);
    }
    
    // End of Yellow Sphere
    
    // Start of Orange Sphere
    
    i = 0;
    for (float phi = -80.0; phi <= 80.0; phi += 1.0) { // 161 times
        float phir = phi * (M_PI/180);
        float phir20 = (phi + 20.0) * (M_PI/180);
        for (float theta = -180; theta <= 180.0; theta+= 1.0) { // 361 times
            float thetar = theta * (M_PI/180);
            vertices[v_index] = v4(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_orange_sphere, vertices[v_index]);
            orangeSphere_vertices[i] = vertices[v_index];
            //colors[v_index] = v4(0, 1, 1, 1);
            v_index = v_index + 1;
            i = i + 1;
            
            vertices[v_index] = v4(sin(thetar) * cos(phir20), cos(thetar) * cos(phir20), sin(phir20), 1.0);
            vertices[v_index] = m4v4_multiplication(temp_orange_sphere, vertices[v_index]);
            orangeSphere_vertices[i] = vertices[v_index];
            //colors[v_index] = v4(0, 1, 1, 1);
            v_index = v_index + 1;
            i = i + 1;
        }
    }
    
    for (a = 929936; a < 1046178; a = a + 3) {
        int m = 4;
        vec4 p0 = vertices[a];
        vec4 p1 = vertices[a + 1];
        vec4 p2 = vertices[a + 2];
        // calculate normal for all three vertices
        p0 = normalize(p0);
        p1 = normalize(p1);
        p2 = normalize(p2);
        
        // calculate ambient, specular, and diffuse
        ambient = v4v4_multiplication(light_ambient, ball_materials[m].reflect_ambient);
        
        vec4 n = normalize(crossProduct(subtractVector(p1, p0), subtractVector(p2, p1)));
        vec4 zeroVec = {0.0, 0.0, 0.0, 1.0};
        // constant shading with distant source
        diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 vector_position = multiplyByScalarVec(v4v4_addition(v4v4_addition(p0, p1), p2), (1.0/3.0));
        vec4 light_vector = subtractVector(lightSource, vector_position);
        diffuse = v4v4_multiplication(light_diffuse, ball_materials[m].reflect_diffuse);
        GLfloat d = dotProduct(n, normalize(light_vector));
        if (d > 0.0) {
            diffuse = multiplyByScalarVec(diffuse, d);
        }
        else {
            diffuse = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        
        specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        vec4 view_direction = normalize(subtractVector(vector_position, zeroVec));
        vec4 half = normalize(v4v4_addition(lightSource, view_direction));
        GLfloat s = dotProduct(half, n);
        if (s > 0.0) {
            specular = multiplyByScalarVec(v4v4_multiplication(light_specular, ball_materials[m].reflect_specular), pow(s, ball_materials[m].shininess));
        }
        else {
            specular = (vec4) {0.0, 0.0, 0.0, 1.0};
        }
        float distance = magnitude(subtractVector(lightSource, vector_position));
        float atten = attenuation(distance);
        // calculate color for the first vertex
        colors[a] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a].w = 1.0;
        
        // calculate color for the second vertex
        colors[a + 1] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 1].w = 1.0;
        
        // calculate color for the third vertex
        colors[a + 2] = v4v4_addition(multiplyByScalarVec(v4v4_addition(specular, diffuse), atten), ambient);
        colors[a + 2].w = 1.0;
    }
    for (j = 0; j < 116242; j++) {
        xShadowHelp = lightSource.y * ((lightSource.x - orangeSphere_vertices[j].x) / (lightSource.y - orangeSphere_vertices[j].y));
        xShadow = lightSource.x - xShadowHelp;
        
        zShadowHelp = lightSource.y * ((lightSource.z - orangeSphere_vertices[j].z) / (lightSource.y - orangeSphere_vertices[j].y));
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
    GLuint program = initShader("//Users/mohitjain/Documents/CS1566_2018/Proj3/Project3/Project3/vshader.glsl", "/Users/mohitjain/Documents/CS1566_2018/Proj3/Project3/Project3/fshader.glsl");
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
    proj_matrix = glGetUniformLocation(program, "projection");
    
        ambient_product_loc = glGetUniformLocation(program, "AmbientProduct");
        diffuse_product_loc = glGetUniformLocation(program, "DiffuseProduct");
        specular_product_loc = glGetUniformLocation(program, "SpecularProduct");
        light_position_loc = glGetUniformLocation(program, "light_position");
        shininess_loc = glGetUniformLocation(program, "shininess");
    
    
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.3, 0.0, 1.0);
    glDepthRange(1,0);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    printf("eyep: %f %f %f \n", eyep.x, eyep.y, eyep.z);
    printf("______________ \n");
     mat4 proj = frustum(-1, 1, -1, 1, 1, -1);
    mat4 mv = look_at(eyep, atp, upv); // switched up curr
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, (GLfloat *) &mv);
        glUniformMatrix4fv(proj_matrix, 1, GL_FALSE, (GLfloat *) &proj);
    
        glUniform4fv(ambient_product_loc, 4, (GLfloat *) &ambient);
        glUniform4fv(diffuse_product_loc, 4, (GLfloat *) &diffuse);
        glUniform4fv(specular_product_loc, 4, (GLfloat *) &specular);
        glUniform4fv(light_position_loc, 4, (GLfloat *) &lightSource);
    float shiny = 10;
    glUniform1f(shininess_loc, (GLfloat) shiny);
    
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 116242);
    glDrawArrays(GL_TRIANGLES, 116242, 116242);
    
    glDrawArrays(GL_TRIANGLES, 232484, 116242);
    glDrawArrays(GL_TRIANGLES, 348726, 116242);
    
    glDrawArrays(GL_TRIANGLES, 464968, 116242);
    glDrawArrays(GL_TRIANGLES, 581210, 116242);
    
    glDrawArrays(GL_TRIANGLES, 697452, 116242);
    glDrawArrays(GL_TRIANGLES, 813694, 116242);
    
    glDrawArrays(GL_TRIANGLES, 929936, 116242);
    glDrawArrays(GL_TRIANGLES, 1046178, 116242);
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
        exit(0);
    else if (key == 'w') {
        lightSource.x += 1;
    }
    else if (key == 'W') {
        lightSource.x -= 1;
    }
    else if (key == 'd') {
        lightSource.y += 1;
    }
    else if (key == 'D') {
        lightSource.y -= 1;
    }
    else if (key == 's') {
        lightSource.z += 1;
    }
    else if (key == 'S') {
        lightSource.z -= 1;
    }
    glutPostRedisplay();
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
        }
        
        glutPostRedisplay();
    }
}


int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("MazeProject");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return 0;
}

