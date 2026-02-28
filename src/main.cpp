#include "vao_wrapper.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <shader.h>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
}


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#define VERTEX_SHADER_PATH "../src/shaders/shader.vert"
#define FRAG_SHADER_PATH "../src/shaders/shader.frag"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    if (!glfwInit()) {
        const char* description;
        int code = glfwGetError(&description);
        throw std::runtime_error(std::string("Failed to initilze glfw: ") + std::string(description));
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH , DEFAULT_WINDOW_HEIGHT, "OpenGL Template", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create a window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to load glad");
    }

    glViewport(0, 0, DEFAULT_WINDOW_WIDTH , DEFAULT_WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader(VERTEX_SHADER_PATH, FRAG_SHADER_PATH);
    std::unique_ptr<float[]> vertices(new float[] {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    });

    std::unique_ptr<float[]> indices (new float[] {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }); 

    VaoWrapper vao(vertices, indices);

    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Color stuff            
        float timeValue = glfwGetTime();
        float greenVal = (sin(timeValue / 2.0)) + 0.5f;
        shader.bind();
        shader.setFloat("fragCol", greenVal);
        vao.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    
    //CleanUp
    {
        glfwTerminate();
    }
    std::cout << "Done\n";
    return 0;
}
