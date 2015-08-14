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

    float points[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint squareVBO = 0;

    glGenBuffers(1, &squareVBO);

    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint squareVAO = 0;

    glGenVertexArrays(1, &squareVAO);

    glBindVertexArray(squareVAO);

    GLuint squareEBO = 0;

    glGenBuffers(1, &squareEBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareEBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Texture ruby = Texture("textures/ruby.png");

    Shader triangle("triangle.vs", "triangle.frag");

    glfwSetKeyCallback(window, keyCallback);

    int width, height;

    glfwGetWindowSize(window, &width, &height);

    GLfloat aspectRatio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);

        ruby.Use();

        glUniform1i(glGetUniformLocation(triangle.program, "ourTexture"), 0);

        triangle.Use();

        GLfloat time = glfwGetTime();

        GLint timeLocation = glGetUniformLocation(triangle.program, "time");

        glUniform1f(timeLocation, time);

        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

        projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.f);

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glUniformMatrix4fv(glGetUniformLocation(triangle.program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));


        glBindVertexArray(squareVAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &squareVAO);

    glDeleteBuffers(1, &squareVBO);

    glDeleteBuffers(1, &squareEBO);
    
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
