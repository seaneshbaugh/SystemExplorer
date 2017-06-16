#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util.cpp"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch);
    ~Camera();

private:
    void UpdateCameraVectors();
};

#endif
