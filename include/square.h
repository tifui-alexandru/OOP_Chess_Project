#ifndef SQUARE_H
#define SQUARE_H
#include <bits/stdc++.h>

class Square {
public:
    int x, y;
    // x  -> row
    // y -> column
    Square(const int &xx, const int &yy) : x(xx), y(yy) {}
    inline std::pair <char, int> chess_notation_pos() const {
        return std::make_pair(y + 1, static_cast<char>(x + 'a'));
    }
};

#endif