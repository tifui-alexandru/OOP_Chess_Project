#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "move.h"
#include <vector>

class Game {
private:
    struct Player {
        std::vector<Piece*> capturedPieces; ///Pieces captured by this player
        int pawnValue;
        PieceColour colour;
        explicit Player(PieceColour colour) : pawnValue(39), colour(colour) {}

        ~Player() {
            for (auto& it : capturedPieces)
                delete it;
            capturedPieces.clear();
        }
    };
    Player *playerToMove, *playerToWait;
    int nrMovesFor50Rule;

    std::vector<Board*> gameBoards;
    std::vector<Move*> gameMoves;

public:
    Game();
    ~Game();
    Board* get_board(int time = -1);
    GameStatus make_move(Square from, Square to);
    void promote(Square pos, PieceType piece);
    GameStatus get_status();

    bool resign;

    void set_resign();

    PieceColour getPlayerToMove();

    inline int get_no_moves() const {return (int)gameMoves.size();}
    inline Move* get_last_move() const {return gameMoves.back();}
};

#endif
