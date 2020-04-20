#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

const int BOARD_SIZE = 8;

struct Square {
    // x -> row
    // y -> column
    int x, y;

    Square(const int &xx, const int &yy) : x(xx), y(yy) {}

    inline std::string chess_notation_pos() const {
        return std::to_string(y + 1) + static_cast<char>(x + 'a');
    }

    inline bool inside_board() const {
        return x >= 0 and y >= 0 and x < BOARD_SIZE and y < BOARD_SIZE;
    }

    Square operator + (const Square &other) const {
        return {x + other.x, y + other.y};
    }

    Square operator * (const Square &other) const {
        return {x * other.x, y + other.y};
    }

    bool operator == (const Square &other) const {
        return x == other.x && y == other.y;
    }
};

#endif //UTILS_H
