#ifndef KING_H
#define KING_H
#include <bits/stdc++.h>
#include "piece.h"

class King : virtual public Piece{
public:
    King(const bool &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

#endif