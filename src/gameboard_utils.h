#ifndef GAMEBOARD_UTILS_H
#define GAMEBOARD_UTILS_H

#include <cassert>
#include <format>

template<typename T>
struct Pos {
    T x;
    T y;
    T z;
};

struct GameBoardPos : Pos<int> {
};

struct MovVector : Pos<int> {
};

struct GLPos : Pos<float> {
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
                pos.x / static_cast<float>(BOARDSIZE.x) * 2.0f - 1.0f,
                pos.y / static_cast<float>(BOARDSIZE.y) * 2.0f - 1.0f,
                0           //probably temp
            };
        };

        static GLPos translateMovVecToGL(const MovVector &pos) {
            return {
                pos.x / static_cast<float>(BOARDSIZE.x) * 2.0f,
                pos.y / static_cast<float>(BOARDSIZE.y) * 2.0f,
                pos.z / static_cast<float>(BOARDSIZE.y) * 2.0f,
            };
        }

        static std::string posToString(const GameBoardPos &pos) {
            return std::format("{}, {}, {}", pos.x, pos.y, pos.z);
        }
        static std::string posToString(const GLPos &pos) {
            return std::format("{}, {}, {}", pos.x, pos.y, pos.z);
        }
        static std::string posToString(const MovVector &pos) {
            return std::format("{}, {}, {}", pos.x, pos.y, pos.z);
        }
};

#endif
