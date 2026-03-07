#ifndef COLOR_H
#define COLOR_H

#include <array>
#include <cassert>
#include <memory>
class Color {
    public:
        Color(int r, int g, int b) {
            assert(r <= MAX_COL_VAL && g <= MAX_COL_VAL && b <= MAX_COL_VAL);
            internalColor[R] = static_cast<float>(r) / MAX_COL_VAL;
            internalColor[G] = static_cast<float>(g) / MAX_COL_VAL;
            internalColor[B] = static_cast<float>(b) / MAX_COL_VAL;
        }

        //returns a copy of the internal color array
        std::unique_ptr<std::array<float, 3>> get() {
            return std::make_unique<std::array<float, 3>>(this->internalColor);
        }


    private:
        std::array<float, 3> internalColor{};
        static constexpr int MAX_COL_VAL = 255;
        static constexpr int R = 0, G = 1, B = 2;
};

#endif
