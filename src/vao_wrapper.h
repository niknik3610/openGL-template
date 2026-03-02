#ifndef VAO_WRAPPER_H
#define VAO_WRAPPER_H

#include <vector>
extern "C" {
#include <cstdint>
}

class VaoWrapper {
    private:
        constexpr static uint32_t VERTEX_SIZE = 3;
        constexpr static uint32_t VERTEX_MAX_COUNT = 6;
        constexpr static uint32_t VERTEX_ARRAY_SIZE = VERTEX_SIZE * VERTEX_MAX_COUNT;

        unsigned int vao, vertexBuf, indexBuf;
        unsigned int currentIndexSize, currentVertexSize;

    public:
        VaoWrapper(const std::vector<float> vertices, const std::vector<unsigned int> indices);
        ~VaoWrapper();
        void draw();
};

#endif
