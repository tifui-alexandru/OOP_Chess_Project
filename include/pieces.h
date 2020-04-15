#ifndef PIECE_H
#define PIECE_H
#include <bits/stdc++.h>
#include "utils.h"

enum PieceType {
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK, 
    QUEEN,
    KING
};

enum PieceColour {
    WHITE, BLACK
};

class Piece {
protected:
    Square position; // 0 indexed
    PieceColour colour;
    PieceType type;
    int value; // value in pawns
    // pawn -> 1 pawn
    // bishop -> 3 pawns
    // knight -> 3 pawns
    // rook -> 5 pawns
    // queen -> 9 pawns

public:
    Piece(const PieceColour &col, const Square &pos, const int &val, const PieceType &tp);
  //  virtual std::vector <Square> get_possible_moves() = 0; -----eroare
};

class King : virtual public Piece {
public:
    King(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

class Queen : virtual public Piece {
public:
    Queen(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

class Rook : virtual public Piece {
public:
    Rook(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

class Knight : virtual public Piece {
public:
    Knight(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

class Bishop : virtual public Piece {
public:
    Bishop(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

class Pawn : virtual public Piece {
public:
    Pawn(const PieceColour &col, const Square &pos);
    std::vector <Square> get_possible_moves();
};

#endif