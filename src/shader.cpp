#include "shader.h"

Shader::Shader(const GLchar* vertexShaderSourceFileName, const GLchar* fragmentShaderSourceFileName) {
    std::string vertexShaderSourceCode = this->ReadShaderSourceFile(vertexShaderSourceFileName);

    std::string fragmentShaderSourceCode = this->ReadShaderSourceFile(fragmentShaderSourceFileName);

    GLuint vertexShader = CreateShaderFromSource(vertexShaderSourceCode, GL_VERTEX_SHADER);

    GLuint fragmentShader = CreateShaderFromSource(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);

    this->program = this->CreateProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(this->program);
}

std::string Shader::ReadShaderSourceFile(std::string shaderSourceFileName) {
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::badbit);

    try {
        shaderFile.open(std::string("shaders/") + shaderSourceFileName);

        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        return shaderStream.str();
    } catch(std::ifstream::failure exception) {
        std::cerr << "Could not read shader file\"" << shaderSourceFileName << "\"." << std::endl;
        
        throw exception;
    }
}

GLuint Shader::CreateShaderFromSource(std::string shaderSourceCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* shaderCode = shaderSourceCode.c_str();

    glShaderSource(shader, 1, &shaderCode, nullptr);

    glCompileShader(shader);

    GLint success = GL_FALSE;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    GLchar infoLog[512];

    if (!success) {
        std::string shaderTypeString;

        switch(shaderType) {
//            case GL_COMPUTE_SHADER:
//                shaderTypeString = "compute";
//
//                break;
            case GL_VERTEX_SHADER:
                shaderTypeString = "vertex";

                break;
//            case GL_TESS_CONTROL_SHADER:
//                shaderTypeString = "tess control";
//
//                break;
//            case GL_TESS_EVALUATION_SHADER:
//                shaderTypeString = "tess evaluation";
//
//                break;
//            case GL_GEOMETRY_SHADER:
//                shaderTypeString = "geometry";
//
//                break;
            case GL_FRAGMENT_SHADER:
                shaderTypeString = "fragment";

                break;
            default:
                shaderTypeString = "unknown";
        }

        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        std::cerr << "Failed to compile " << shaderTypeString << " shader." << std::endl << infoLog << std::endl;

        throw std::runtime_error(std::string("Failed to compile ") + shaderTypeString + std::string(" shader."));
    }

    return shader;
}

GLuint Shader::CreateProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);

    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint success = GL_FALSE;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        GLchar infoLog[512];

        glGetProgramInfoLog(program, 512, nullptr, infoLog);

        std::cerr << "Failed to link shader program." << std::endl << infoLog << std::endl;

        throw std::runtime_error("Failed to link shader program.");
    }

    return program;
}
