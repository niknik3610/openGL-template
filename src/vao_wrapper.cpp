#include "vao_wrapper.h"
#include <vector>

extern "C" {
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
}

VaoWrapper::VaoWrapper(const std::shared_ptr<std::vector<float>> vertices, const std::shared_ptr<std::vector<unsigned int>> indices) {
    this->vertices = vertices;
    this->indices = indices;

    glGenVertexArrays(1, &vao);

    unsigned int bufs[2]{}; 
    glGenBuffers(2, bufs);
    vertexBuf = bufs[0], indexBuf = bufs[1];

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_STATIC_DRAW);      //performs a copy so should be safe to clear array here
                                                                                                            
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);

    //set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}


VaoWrapper::~VaoWrapper() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexBuf);
    glDeleteBuffers(1, &indexBuf);
}

void VaoWrapper::draw() 
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, this->currentIndexSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void VaoWrapper::reBindVertexBuff() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_STATIC_DRAW);      //performs a copy so should be safe to clear array here
}

void VaoWrapper::reBindIndexBuff() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);
}
