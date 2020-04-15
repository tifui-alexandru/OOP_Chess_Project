#ifndef PIECE_H
#define PIECE_H
#include <bits/stdc++.h>
#include "square.h"

class Piece {
protected:
    Square position; // 0 indexed
    bool colour; // false -> white, true -> black
    int type;
    // 0 -> pawn
    // 1 -> bishop
    // 2 -> knight
    // 3 -> rook
    // 4 -> queen
    // 5 -> king
    int value; // value in pawns
    // pawn -> 1 pawn
    // bishop -> 3 pawns
    // knight -> 3 pawns
    // rook -> 5 pawns
    // queen -> 9 pawns

    // N S E W NE NW SE SW
    // static const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    // static const int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

public:
    Piece(const bool &col, const Square &pos, const int &val, const int &tp);
};
#endif