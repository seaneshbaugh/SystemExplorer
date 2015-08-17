#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(8.0f), mouseSensitivity(0.05f), zoom(45.0f) {
    this->position = position;

    this->worldUp = worldUp;

    this->yaw = yaw;

    this->pitch = pitch;

    this->UpdateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(8.0f), mouseSensitivity(0.05f), zoom(45.0f) {
    this->position = glm::vec3(posX, posY, posZ);

    this->worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);

    this->yaw = yaw;

    this->pitch = pitch;

    this->UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboardInput(CameraMovement direction, GLfloat deltaTime) {
    GLfloat velocity = this->movementSpeed * deltaTime;

    if (direction == FORWARD) {
        this->position += this->front * velocity;
    }

    if (direction == BACKWARD) {
        this->position -= this->front * velocity;
    }

    if (direction == LEFT) {
        this->position -= this->right * velocity;
    }

    if (direction == RIGHT) {
        this->position += this->right * velocity;
    }
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
    xOffset *= this->mouseSensitivity;

    yOffset *= this->mouseSensitivity;

    this->yaw += xOffset;

    this->pitch += yOffset;

    if (constrainPitch) {
        if (this->pitch > 89.0f) {
            this->pitch = 89.0f;
        } else {
            if (this->pitch < -89.0f) {
                this->pitch = -89.0f;
            }
        }
    }

    this->UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset) {
    if (this->zoom >= 1.0f && this->zoom <= 45.0f) {
        this->zoom -= yOffset;
    } else {
        if (this->zoom <= 1.0f) {
            this->zoom = 1.0f;
        } else {
            if (this->zoom >= 45.0f) {
                this->zoom = 45.0f;
            }
        }
    }
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front;

    front.x = std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));

    front.y = std::sin(glm::radians(this->pitch));

    front.z = std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch));

    this->front = glm::normalize(front);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));

    this->up = glm::normalize(glm::cross(this->right, this->front));
}