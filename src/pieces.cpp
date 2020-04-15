#include <bits/stdc++.h>
#include "../include/pieces.h"
#include "../include/utils.h"

// N S E W NE NW SE SW
static const Square directions[8] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

Piece::Piece(const PieceColour &col, const Square &pos, const int &val, const PieceType &tp) : colour(col), position(pos), value(val), type(tp) {}

King::King(const PieceColour &col, const Square &pos) : Piece(col, pos, 0, KING) {}
Queen::Queen(const PieceColour &col, const Square &pos) : Piece(col, pos, 9, QUEEN) {}
Rook::Rook(const PieceColour &col, const Square &pos) : Piece(col, pos, 5, ROOK) {}
Knight::Knight(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, KNIGHT) {}
Bishop::Bishop(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, BISHOP) {}
Pawn::Pawn(const PieceColour &col, const Square &pos) : Piece(col, pos, 1, PAWN) {}

std::vector <Square> King::get_possible_moves() {
    std::vector <Square> ans;
    for (auto& idx : directions) {
        Square temp = position + idx;
        if (temp.valid()) 
            ans.emplace_back(temp);
    }
    return ans;
}