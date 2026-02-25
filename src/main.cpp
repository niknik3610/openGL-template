#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <format>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
}


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

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

    unsigned int vertexShader;
    {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            throw std::runtime_error(std::format("Failed to compile vertex shader: {}", infoLog));
        }
    }

    unsigned int fragmentShader;
    {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragShaderSource , NULL);
        glCompileShader(fragmentShader);

        int  success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            throw std::runtime_error(std::format("Failed to compile fragment shader: {}", infoLog));
        }
    }

    unsigned int shaderProgram;
    {
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int  success;
        char infoLog[512];
        glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
            throw std::runtime_error(std::format("Failed to compile fragment shader: {}", infoLog));
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    unsigned int vao, vertexBuf, indexBuf;
    {
        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        }; 

        glGenVertexArrays(1, &vao);
        
        unsigned int bufs[2] = {}; 
        glGenBuffers(2, bufs);
        vertexBuf = bufs[0], indexBuf = bufs[1];

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //performs a copy so should be safe to clear array here

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
                                                                                        
        //set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }


    int vertexColorLocation = glGetUniformLocation(shaderProgram, "fragCol");
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Color stuff            
        float timeValue = glfwGetTime();
        float greenVal = (sin(timeValue / 2.0)) + 0.5f;
        glUseProgram(shaderProgram);     

        glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    
    //CleanUp
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vertexBuf);
        glDeleteBuffers(1, &indexBuf);
        glDeleteProgram(shaderProgram);
        glfwTerminate();
    }
    std::cout << "Done\n";
    return 0;
}
