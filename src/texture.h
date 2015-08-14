#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <exception>
#include <iostream>
#include <GL/glew.h>

#include "../lib/soil/soil.h"

class Texture
{
public:
    GLuint texture;

    Texture(const GLchar* textureFileName);
    ~Texture();
    void Use();
};

#endif