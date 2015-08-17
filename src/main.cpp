#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>

#include "../lib/soil/soil.h"

#include "shader.h"
#include "texture.h"
#include "cube.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLFWwindow* CreateWindow();

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

    int width, height;

    glfwGetWindowSize(window, &width, &height);

    GLfloat aspectRatio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

    Cube cube = Cube();

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        checkerboard.Use();

        glUniform1i(glGetUniformLocation(triangle.program, "ourTexture"), 0);

        triangle.Use();

        GLfloat time = glfwGetTime();

        GLint timeLocation = glGetUniformLocation(triangle.program, "time");

        glUniform1f(timeLocation, time);

        glm::mat4 viewMatrix;

        glm::mat4 projectionMatrix;

        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

        projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.f);

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        cube.Use();

        for (GLuint i = 0; i < 10; i += 1) {
            glm::mat4 modelMatrix;

            modelMatrix = glm::translate(modelMatrix, cubePositions[i]);

            GLfloat angle = 20.0f * (i * 5 + 1) * time / 360.0f;

            modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.3f, 0.5f));

            glUniformMatrix4fv(glGetUniformLocation(triangle.program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
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
