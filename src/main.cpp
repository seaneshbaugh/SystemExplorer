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

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    float points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    GLuint vbo = 0;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glEnableVertexAttribArray (0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4 (vp, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vs, 1, &vertex_shader, NULL);

    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, &fragment_shader, NULL);

    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, fs);

    glAttachShader(shader_program, vs);

    glLinkProgram(shader_program);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}
