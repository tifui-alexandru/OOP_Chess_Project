#include <bits/stdc++.h>
#include "pieces.h"

// N S E W NE NW SE SW
static const Square directions[8] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

Piece::Piece(const PieceColour &col = WHITE, const Square &pos = {-1, -1}, const int &val = 0, const PieceType &tp = PAWN) : colour(col), position(pos), value(val), type(tp) {
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

King::King(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, KING) {}
Queen::Queen(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, QUEEN) {}
Rook::Rook(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, ROOK) {}
Knight::Knight(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, KNIGHT) {}
Bishop::Bishop(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, BISHOP) {}
Pawn::Pawn(const PieceColour &col = WHITE, const Square &pos = {-1, -1}) : Piece(col, pos, 0, PAWN) {}

std::vector <Square> King::get_possible_moves() {
    std::vector <Square> ans;
    for (auto& idx : directions) {
        Square temp = position + idx;
        if (temp.valid()) 
            ans.emplace_back(temp);
    }
    return ans;
}