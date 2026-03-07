#ifndef COLOR_H
#define COLOR_H

#include <array>
#include <cassert>
#include <cmath>
class Color {
    public:
        Color(int r, int g, int b) {
            assert(r <= MAX_COL_VAL && g <= MAX_COL_VAL && b <= MAX_COL_VAL);
            this->internalColor[R] = r, this->internalColor[G] = g, this->internalColor[B] = b;
        }

        //returns a copy of the internal color array (because int is a primitive this should work even with shallow copy
        std::array<int, 3> get() {
            return this->internalColor;
        }

        std::array<float, 3> getPrepared() {
            std::array<float, 3> cpy{};
            cpy[R] = static_cast<float>(this->internalColor[R]) / MAX_COL_VAL;
            cpy[G] = static_cast<float>(this->internalColor[G]) / MAX_COL_VAL;
            cpy[B] = static_cast<float>(this->internalColor[B]) / MAX_COL_VAL;

            return std::move(cpy);
        }

        void modify(int r, int g, int b) {
            assert(r <= MAX_COL_VAL && g <= MAX_COL_VAL && b <= MAX_COL_VAL);
            this->internalColor[R] = r, this->internalColor[G] = g, this->internalColor[B] = b;
         }

    private:
        std::array<int, 3> internalColor{};
        static constexpr int MAX_COL_VAL = 255;
        static constexpr int R = 0, G = 1, B = 2;
};

#endif
