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

class Piece;

typedef std::vector<std::vector<Piece*> > BoardType;

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
    int no_moves;

public:
    Piece(const PieceColour &col, const Square &pos, const int &val, const PieceType &tp, int no_moves = 0);

    virtual Piece* Clone() = 0;
    virtual std::vector <Square> get_possible_moves(const BoardType &board) = 0;

    inline PieceColour get_colour() const {return colour;}
    inline PieceType get_type() const {return type;}
    inline int get_value() const {return value;}
    
    inline void set_position(const Square &pos) {position = pos;}
    inline void inc_no_moves() {++no_moves;}

    inline bool moved() const{return static_cast<bool>(no_moves);}
};

class King : virtual public Piece {
public:
    King(const PieceColour &col, const Square &pos);
    King(const King &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves) {}
    Piece* Clone() override {
        return new King(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
};

class Queen : virtual public Piece {
public:
    Queen(const PieceColour &col, const Square &pos);
    Queen(const Queen &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves) {}
    Piece* Clone() override {
        return new Queen(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
};

class Rook : virtual public Piece {
public:
    Rook(const PieceColour &col, const Square &pos);
    Rook(const Rook &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves) {}
    Piece* Clone() override {
        return new Rook(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
};

class Knight : virtual public Piece {
public:
    Knight(const PieceColour &col, const Square &pos) ;
    Knight(const Knight &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves) {}
    Piece* Clone() override {
        return new Knight(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
};

class Bishop : virtual public Piece {
public:
    Bishop(const PieceColour &col, const Square &pos);
    Bishop(const Bishop &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves) {}
    Piece* Clone() override {
        return new Bishop(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
};

class Pawn : virtual public Piece {
private:
    bool can_be_captured_en_passant;

public:
    Pawn(const PieceColour &col, const Square &pos);
    Pawn(const Pawn &obj) : Piece(obj.colour, obj.position, obj.value, obj.type, obj.no_moves), can_be_captured_en_passant(0) {}
    Piece* Clone() override {
        return new Pawn(*this);
    }
    std::vector <Square> get_possible_moves(const BoardType &board) override;
    
    inline bool get_en_passant() const {return can_be_captured_en_passant;}
    inline void set_en_passant(const bool &vl) {can_be_captured_en_passant = vl;}
};

#endif