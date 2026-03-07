#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include <array>
#include "shader.h"
#include "vao_wrapper.h"

struct Pos {
    float x;
    float y;
    float z;
};

class Square {
    public:
        /** 
         * Expects Pos to be in screenspace coordinates! Use utils function to translate from game coordinates
         * */
        Square(std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader, std::array<float, 3> color, Pos pos);

        void setPos(Pos pos);
        void translatePos(Pos* movementVector);
        void draw();
        void setColor(std::unique_ptr<std::array<float, 3>> color);

    private:
        std::shared_ptr<VaoWrapper> vao;
        std::shared_ptr<Shader> shader;

        Pos pos;
        std::array<float, 3> color;
};
#endif
