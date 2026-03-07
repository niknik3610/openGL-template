#include "square.h"

#include "shader.h"
#include "vao_wrapper.h"
#include <array>
#include <memory>

Square::Square(std::shared_ptr<VaoWrapper> vao, std::shared_ptr<Shader> shader, std::array<float, 3> color, GLPos pos) : 
    vao(vao), pos(std::move(pos)), color(std::move(color)), shader(shader), posChanged(true) 
{ 
}

void Square::setPos(GLPos pos) {
    this->pos = pos;
}

void Square::translatePos(const GLPos& movementVector) {
    this->pos.x += movementVector.x;
    this->pos.y += movementVector.y;
    this->pos.z += movementVector.z;
    this->posChanged = true;
}


void Square::setColor(std::array<float, 3> color) {
    this->color = std::move(color);
}

void Square::draw() {
    this->shader->bind();
    this->shader->set3f("color", this->color);

    if (this->posChanged) {
        this->cachedPos = {pos.x, pos.y, pos.z};
        this->posChanged = false;
    }

    this->shader->set3f("offset", this->cachedPos);
    this->posChanged = false;

    this->vao->reBindVertexBuff();
    this->vao->draw();
}
