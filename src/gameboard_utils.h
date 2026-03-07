#ifndef GAMEBOARD_UTILS_H
#define GAMEBOARD_UTILS_H

#include "square.h"
#include <cassert>

struct GameBoardPos {
    int x;
    int y;
    int z;
};

class GameBoardUtils {
    public:
        //TODO: probably make this program arg
        static constexpr GameBoardPos BOARDSIZE = {
            10,
            10,
            10
        };

        static GLPos translateBoardCoordsToGL(const GameBoardPos &pos) {
            //handling going out of bounds should be done by calling class (or not we see)
            assert(pos.x < BOARDSIZE.x && pos.y < BOARDSIZE.y && pos.z < BOARDSIZE.z);

            //map to 0-2, then subtract 1 to get pos
            return {
                static_cast<float>(pos.x) / BOARDSIZE.x * 2 - 1,
                static_cast<float>(pos.y) / BOARDSIZE.y * 2 - 1,
                static_cast<float>(pos.z) / BOARDSIZE.z * 2 - 1
            };
        }
};

#endif
