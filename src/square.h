#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include <array>
#include "shader.h"
#include "vao_wrapper.h"

struct GLPos {
    float x;
    float y;
    float z;
};

class Square {
    public:
        /** 
         * Expects Pos to be in screenspace coordinates! Use utils function to translate from game coordinates
         * */
        Square(std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader, std::array<float, 3> color, GLPos pos);

        void setPos(GLPos pos);
        void translatePos(const GLPos& movementVector);
        void draw();
        void setColor(std::array<float, 3> color);

    private:
        std::shared_ptr<VaoWrapper> vao;
        std::shared_ptr<Shader> shader;

        GLPos pos;
        std::array<float, 3> color;

        std::array<float, 3> cachedPos;

        bool posChanged;

};
#endif
