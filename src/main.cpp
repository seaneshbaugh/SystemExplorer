#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>
#include <math.h>

#include "../lib/soil/soil.h"

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "cube.h"

// OMG global variables, yuck.
GLfloat lastX;
GLfloat lastY;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool allowInput = true;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

GLFWwindow* CreateWindow();
void Move();

int main(int argc, const char * argv[]) {
    glfwSetErrorCallback([] (int error, const char* description) {
        std::cerr << description << std::endl;
    });

    if (!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = CreateWindow();

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;

        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewInit();

    const GLubyte* openGLRenderer = glGetString(GL_RENDERER);

    const GLubyte* openGLVersion = glGetString(GL_VERSION);

    std::cout << "Renderer: " << openGLRenderer << std::endl;

    std::cout << "OpenGL version supported: " << openGLVersion << std::endl;

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    Texture checkerboard = Texture("textures/checkerboard.png");

    Shader triangle("triangle.vs", "triangle.frag");

    glfwSetKeyCallback(window, keyCallback);

    glfwSetCursorPosCallback(window, mouseCallback);

    int width, height;

    glfwGetWindowSize(window, &width, &height);

    GLfloat aspectRatio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

    lastX = static_cast<GLfloat>(width) / 2.0;

    lastY = static_cast<GLfloat>(height) / 2.0;

    Cube cube = Cube();

    std::random_device rd;

    std::mt19937 mt(rd());

    std::uniform_int_distribution<float> dist(-150.0f, 150.0f);

    glm::vec3 cubePositions[5000];

    for (size_t i = 0; i < 5000; i += 1) {
        cubePositions[i] = glm::vec3(dist(mt), dist(mt), dist(mt));
    }

    for (size_t i = 0; i < 1024; i += 1) {
        keys[i] = false;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        GLfloat currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;

        lastFrame = currentFrame;

        Move();

        checkerboard.Use();

        glUniform1i(glGetUniformLocation(triangle.program, "ourTexture"), 0);

        triangle.Use();

        GLfloat time = glfwGetTime();

        GLint timeLocation = glGetUniformLocation(triangle.program, "time");

        glUniform1f(timeLocation, time);

        glm::mat4 viewMatrix;

        glm::mat4 projectionMatrix;


        if (allowInput) {
            viewMatrix = camera.GetViewMatrix();
        } else {
            camera.ProcessMouseMovement(5.0f, 0.0f);

            viewMatrix = camera.GetViewMatrix();
        }

        projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 400.f);

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        cube.Use();

        for (GLuint i = 0; i < 5000; i += 1) {
            glm::mat4 modelMatrix;

            modelMatrix = glm::translate(modelMatrix, cubePositions[i]);

            GLfloat angle = 20.0f * (((i * 5) % 10) + 1) * time / 360.0f;

            modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.3f, 0.5f));

            glUniformMatrix4fv(glGetUniformLocation(triangle.program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    
    return 0;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        allowInput = !allowInput;
    }

    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else {
        if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse = true;

    if (allowInput) {
        if (firstMouse) {
            lastX = xpos;

            lastY = ypos;

            firstMouse = false;
        }

        GLfloat xOffset = xpos - lastX;

        GLfloat yOffset = lastY - ypos;

        lastX = xpos;

        lastY = ypos;

        camera.ProcessMouseMovement(xOffset, yOffset);
    }
}

GLFWwindow* CreateWindow() {
    int monitorCount;

    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    if (monitorCount < 1) {
        return nullptr;
    }

    GLFWmonitor* largestMonitor = monitors[0];

    const GLFWvidmode* largestVidmode = glfwGetVideoMode(largestMonitor);

    for (int i = 1; i < monitorCount; i += 1) {
        const GLFWvidmode* vidmode = glfwGetVideoMode(monitors[i]);

        if (vidmode->width * vidmode->height > largestVidmode->width * largestVidmode->height) {
            largestVidmode = vidmode;

            largestMonitor = monitors[i];
        }
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(largestVidmode->width, largestVidmode->height, "System Explorer", largestMonitor, nullptr);

    return window;
}

void Move() {
    if (allowInput) {
        if (keys[GLFW_KEY_W]) {
            camera.ProcessKeyboardInput(FORWARD, deltaTime);
        }

        if (keys[GLFW_KEY_S]) {
            camera.ProcessKeyboardInput(BACKWARD, deltaTime);
        }

        if (keys[GLFW_KEY_A]) {
            camera.ProcessKeyboardInput(LEFT, deltaTime);
        }

        if (keys[GLFW_KEY_D]) {
            camera.ProcessKeyboardInput(RIGHT, deltaTime);
        }
    }
}
