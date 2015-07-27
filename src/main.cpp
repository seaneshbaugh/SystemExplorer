#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

int main(int argc, const char * argv[]) {
    if (!glfwInit()) {
        return 1;
    }

    int monitorCount;

    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    GLFWmonitor* largestMonitor = monitors[0];

    const GLFWvidmode* largestVidmode = glfwGetVideoMode(largestMonitor);

    for (int i = 1; i < monitorCount; i += 1) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);

        if (mode->width * mode->height > largestVidmode->width * largestVidmode->height) {
            largestVidmode = mode;

            largestMonitor = monitors[i];
        }
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(largestVidmode->width, largestVidmode->height, "System Explorer", largestMonitor, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;

        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);

    const GLubyte* version = glGetString(GL_VERSION);

    printf("Renderer: %s\n", renderer);

    printf("OpenGL version supported: %s\n", version);

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}
