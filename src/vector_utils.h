#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <cassert>
#include <memory>
#include <vector>

#define X 0
#define Y 1
#define Z 2

template<typename T>
void translateVector(std::shared_ptr<std::vector<T>> vec, T xTrans, T yTrans, T zTrans) {
    assert(vec->size() % 3 == 0);

    for (int i = 0; i < vec->size(); i += 3) {
        auto vector = vec.get()->data();
        vector[i + X] += xTrans;
        vector[i + Y] += yTrans;
        vector[i + Z] += zTrans;
    }
}
#endif
