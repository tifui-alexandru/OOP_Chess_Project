#ifndef UTILS_H
#define UTILS_H

#include <string>

const int BOARD_SIZE = 8;

struct Square {
    // x -> row
    // y -> column
    int x, y;

    Square(const int &xx = 0, const int &yy = 0) : x(xx), y(yy) {}

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
        return {x * other.x, y * other.y};
    }

    bool operator == (const Square &other) const {
        return x == other.x && y == other.y;
    }

    inline Square reverse() const {
        return {7 - x, y};
    }
};

inline Square my_notation_pos(const std::string s) {
    return Square(s[1] - 'a', s[0] - '0' - 1);
}

class ButtonBox {
public:
    std::pair <int, int> topLeft, bottomRight;
    ButtonBox(const int &x1 = 0, const int &y1 = 0, const int &x2 = 0, const int &y2 = 0) {
        topLeft = std::make_pair(x1, y1);
        bottomRight = std::make_pair(x2, y2);
    }

    inline bool isInside(const int &x, const int &y) const {
        return (topLeft.first <=x and x <= bottomRight.first and topLeft.second <= y and y <= bottomRight.second);
    }
};

#endif //UTILS_H
