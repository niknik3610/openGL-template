#ifndef VAO_WRAPPER_H
#define VAO_WRAPPER_H

#include <vector>
#include <memory>
extern "C" {
#include <cstdint>
}

class VaoWrapper {
    private:
        constexpr static uint32_t VERTEX_SIZE = 3;
        constexpr static uint32_t VERTEX_MAX_COUNT = 6;
        constexpr static uint32_t VERTEX_ARRAY_SIZE = VERTEX_SIZE * VERTEX_MAX_COUNT;
        
        std::shared_ptr<std::vector<float>> vertices;
        std::shared_ptr<std::vector<unsigned int>> indices;

        unsigned int vao, vertexBuf, indexBuf;
        unsigned int currentIndexSize, currentVertexSize;

    public:
        VaoWrapper(const std::shared_ptr<std::vector<float>> vertices, const std::shared_ptr<std::vector<unsigned int>> indices);
        ~VaoWrapper();

        void reBindVertexBuff();
        void reBindIndexBuff();
        void draw();

        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
};

#endif
