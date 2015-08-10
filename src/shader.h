#ifndef __SHADER_H__
#define __SHADER_H__

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>


class Shader
{
public:
    GLuint program;

    Shader(const GLchar* vertexSourceName, const GLchar* fragmentSourceName);
    void Use();
};

#endif
