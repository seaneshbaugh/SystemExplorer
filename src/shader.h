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

    Shader(const GLchar* vertexShaderSourceFileName, const GLchar* fragmentShaderSourceFileName);
    void Use();

private:
    std::string ReadShaderSourceFile(std::string shaderSourceFileName);
    GLuint CreateShaderFromSource(std::string shaderSourceCode, GLenum shaderType);
    GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif
