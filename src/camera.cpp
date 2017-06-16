#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(8.0f), mouseSensitivity(0.05f), zoom(45.0f) {
    this->position = position;

    this->worldUp = worldUp;

    this->yaw = yaw;

    this->pitch = util::constrain<GLfloat>(pitch, -90.0f, 90.0f);

    this->UpdateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(8.0f), mouseSensitivity(0.05f), zoom(45.0f) {
    this->position = glm::vec3(posX, posY, posZ);

    this->worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);

    this->yaw = yaw;

    this->pitch = util::constrain<GLfloat>(pitch, -90.0f, 90.0f);

    this->UpdateCameraVectors();
}

Camera::~Camera() {
    
}

void Camera::UpdateCameraVectors() {

}
