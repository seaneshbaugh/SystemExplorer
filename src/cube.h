#ifndef __CUBE_H__
#define __CUBE_H__

#include <GL/glew.h>

class Cube
{
public:
    GLuint VBO;
    GLuint VAO;

    Cube();
    ~Cube();
    void Use();
};

#endif