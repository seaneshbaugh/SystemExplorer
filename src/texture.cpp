#include "texture.h"

Texture::Texture(const GLchar* textureFileName) {
    glGenTextures(1, &this->texture);

    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;

    unsigned char* image = SOIL_load_image(textureFileName, &width, &height, 0, SOIL_LOAD_RGB);

    if (image == nullptr) {
        std::cerr << SOIL_last_result() << std::endl;

        throw std::runtime_error(SOIL_last_result());
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}

void Texture::Use() {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}