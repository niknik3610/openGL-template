#include <format>
#include <fstream>
#include <shader.h>
#include <sstream>
#include <stdexcept>
#include <string>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
}

Shader::Shader(const std::string &vertPath, const std::string &fragPath) {
    std::string vertCode = this->loadShaderFileFromDisk(vertPath);
    std::string fragCode = this->loadShaderFileFromDisk(fragPath);

    int vertShaderId = this->compileShader(GL_VERTEX_SHADER, std::move(vertCode));
    int fragShaderId = this->compileShader(GL_FRAGMENT_SHADER, std::move(fragCode));

    //TODO: this needs error handling
    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShaderId);
    glAttachShader(shaderProgram, fragShaderId);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
}


std::string Shader::loadShaderFileFromDisk(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error(std::format("File: {} failed to open", path));
    }

    std::stringstream fileBuff;
    fileBuff << file.rdbuf();

    return std::move(fileBuff.str());
}

unsigned int Shader::compileShader(int shaderType, std::string shaderSource)
{
    const char* shaderSourceC = shaderSource.c_str();

    int id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderSourceC, NULL);
    glCompileShader(id);

    int  success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        throw std::runtime_error(std::format("Failed to compile shader: {}", infoLog));
    }
    return id;
}

void Shader::bind() {
    glUseProgram(this->shaderProgram);     
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), static_cast<int>(value));
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}
