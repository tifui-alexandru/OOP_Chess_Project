#include <bits/stdc++.h>
#include "piece.h"

Piece::Piece(const bool &col = false, const Square &pos = {-1, -1}, const int &val = 0, const int &tp = 0) : colour(col), position(pos), value(val), type(tp) {
    if (position.x == -1) {
        assert(tp <= 3);
        if (tp == 4) {
            if (col) position = {7, 3};
            else position = {0, 3};
        }
        else {
            if (col) position = {7, 4};
            else position = {0, 4};
        }
    }
}