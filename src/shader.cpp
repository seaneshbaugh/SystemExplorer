#include "shader.h"

class myexception: public std::exception {
    virtual const char* what() const throw()
    {
        return "My exception happened";
    }
} ShaderException;

Shader::Shader(const GLchar* vertexSourceName, const GLchar* fragmentSourceName) {
    std::string vertexShaderSourceCode;
    std::string fragmentShaderSourceCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::badbit);

    fragmentShaderFile.exceptions(std::ifstream::badbit);

    try {
        vertexShaderFile.open(std::string("shaders/") + vertexSourceName);

        std::stringstream vertexShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();

        vertexShaderFile.close();

        vertexShaderSourceCode = vertexShaderStream.str();

        fragmentShaderFile.open(std::string("shaders/") + fragmentSourceName);

        std::stringstream fragmentShaderStream;

        fragmentShaderStream << fragmentShaderFile.rdbuf();

        fragmentShaderFile.close();

        fragmentShaderSourceCode = fragmentShaderStream.str();
    } catch(std::ifstream::failure exception) {
        std::cerr << "Could not read shader file\"" << vertexSourceName << "\"." << std::endl;

        throw exception;
    }

    const GLchar* vertexShaderCode = vertexShaderSourceCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);

    glCompileShader(vertexShader);

    GLint success = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    GLchar infoLog[512];

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cerr << "Failed to compile vertex shader \"" << vertexSourceName << "\"." << std::endl << infoLog << std::endl;

        throw std::runtime_error(std::string("Failed to compile vertex shader \"") + vertexSourceName + std::string("\"."));
    }

    const GLchar* fragmentShaderCode = fragmentShaderSourceCode.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

        std::cerr << "Failed to compile fragment shader\"" << fragmentSourceName << "\"." << std::endl << infoLog << std::endl;

        throw std::runtime_error(std::string("Failed to compile fragment shader\"") + fragmentSourceName + std::string("\"."));
    }

    this->program = glCreateProgram();

    glAttachShader(this->program, vertexShader);

    glAttachShader(this->program, fragmentShader);

    glLinkProgram(this->program);

    glGetProgramiv(this->program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->program, 512, nullptr, infoLog);

        std::cerr << "Failed to link shader program." << std::endl << infoLog << std::endl;

        throw std::runtime_error("Failed to link shader program.");
    }

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(this->program);
}
