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

std::vector <Square> Queen::get_possible_moves() {
    std::vector <Square> ans;
    for (int dim = 1; dim <= 7; ++dim)
        for (auto& idx : directions) {
            Square temp = position + (idx * Square(dim, dim));
            if (temp.valid())
                ans.emplace_back(temp);
        }
    return ans;
}

std::vector <Square> Rook::get_possible_moves() {
    std::vector <Square> ans;
    for (int dim = 1; dim <= 7; ++dim)
        for (int idx = 0; idx < 4; ++idx) {
            Square temp = position + (directions[idx] * Square(dim, dim));
            if (temp.valid())
                ans.emplace_back(temp);
        }   
    return ans;
}

std::vector <Square> Knight::get_possible_moves() {
    std::vector <Square> ans;
    for (int idx = 5; idx < 8; ++idx) {
        Square temp1 = position + directions[idx] + (directions[idx] * Square(1, 0));
        Square temp2 = position + directions[idx] + (directions[idx] * Square(0, 1));

        if (temp1.valid())
            ans.emplace_back(temp1);
        if (temp2.valid())
            ans.emplace_back(temp2);
    }
    return ans;
}

std::vector <Square> Bishop::get_possible_moves() {
    std::vector <Square> ans;
    for (int dim = 1; dim <= 7; ++dim)
        for (int idx = 5; idx < 8; ++idx) {
            Square temp = position + (directions[idx] * Square(dim, dim));
            if (temp.valid())
                ans.emplace_back(temp);
        }   
    return ans;
}

std::vector <Square> Pawn::get_possible_moves() {
    std::vector <Square> ans;
    Square temp(0, 0);
    if (colour == WHITE) {
        ans.emplace_back(position + Square(1, 0));
        temp = position + Square(1, 1);
        if (temp.valid())
            ans.emplace_back(temp);
        temp = position + Square(1, -1);
        if (temp.valid())
            ans.emplace_back(temp);
    }
    else {
        ans.emplace_back(position + Square(-1, 0));
        temp = position + Square(-1, -1);
         if (temp.valid())
            ans.emplace_back(temp);
        Square temp = position + Square(-1, 1);
    }
    return ans;
}