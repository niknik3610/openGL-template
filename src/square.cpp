#include "square.h"

#include "shader.h"
#include "vao_wrapper.h"
#include <array>
#include <memory>

Square::Square(std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader, std::array<float, 3> color, Pos pos) : 
    vao(vao), pos(std::move(pos)), color(std::move(color)), shader(shader) 
{ 
}

void Square::setPos(Pos pos) {
    this->pos = pos;
}

void Square::translatePos(Pos movementVector) {
    this->pos.x += movementVector.x;
    this->pos.y += movementVector.y;
    this->pos.z += movementVector.z;
}

void Square::draw() {
    this->vao->reBindVertexBuff();
    this->shader->bind();

    this->shader->set3f("color", this->color);
    //TODO: cache this if not translated
    
    std::array<float, 3> posArr{pos.x, pos.y, pos.z};
    this->shader->set3f("offset", posArr);

    this->vao->draw();
}
