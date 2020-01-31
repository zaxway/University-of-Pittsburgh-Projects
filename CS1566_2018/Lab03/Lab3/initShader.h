//
//  initShader.h
//  triangle_2
//
//  Created by Mohit Jain on 9/8/17.
//  Copyright © 2017 Mohit Jain. All rights reserved.
//

#ifndef initShader_h
#define initShader_h



/*
 * initShader.h
 *
 *  Created on: Aug 28, 2017
 *      Author: Thumrongsak Kosiyatrakul
 */



#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>



struct Shader
{
    const char*  filename;
    GLenum       type;
    GLchar*      source;
};

GLuint initShader(const char* vertexShaderFile, const char* fragmentShaderFile);


#endif /* initShader_h */

