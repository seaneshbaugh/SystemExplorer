#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(8.0f), mouseSensitivity(0.05f), zoom(45.0f) {
    this->position = position;

    this->worldUp = worldUp;

    this->yaw = yaw;

    this->pitch = pitch;

    this->UpdateCameraVectors();
}

Camera::~Camera() {
    
}

void Camera::UpdateCameraVectors() {

}
