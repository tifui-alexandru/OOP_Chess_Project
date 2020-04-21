#include "../include/utils.h"
#include "../include/game.h"
#include <vector>

Game::Game() {
    playerToMove = new Player(WHITE);
    playerToWait = new Player(BLACK);
    gameBoards.push_back(new Board);
}

Board* Game::get_board(int time) {
    assert(time >= -1 && time < gameBoards.size());
    if(time == -1) return gameBoards.back();
    return gameBoards[time];
}

GameStatus Game::make_move(Square from, Square to) {
    auto currBoard = new Board(gameBoards.back());
    if(auto toPiece = currBoard->get_piece(to)) {
        playerToMove->capturedPieces.push_back(toPiece);
        playerToWait->pawnValue -= toPiece->get_value();
    }
    else if (currBoard->get_piece(from)->get_type() == PAWN and to.y != from.y) { // en passant
        auto capturedPawn = currBoard->get_piece(from + Square(0, to.y - from.y));
        playerToMove->capturedPieces.push_back(capturedPawn);
        playerToWait->pawnValue -= 1;
        currBoard->change_position(nullptr, from + Square(0, to.y - from.y));
    }

    auto fromPiece = currBoard->get_piece(from);
    fromPiece->inc_no_moves();
    currBoard->change_position(fromPiece, to);
    currBoard->change_position(nullptr, from);
    gameMoves.push_back(new Move(from, to, gameBoards.back(), currBoard, playerToMove->colour));
    gameBoards.push_back(currBoard);

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (auto currPiece = currBoard->get_piece({i, j})) {
                if (currPiece->get_type() == PAWN and currPiece->get_colour() == playerToMove->colour)
                    dynamic_cast<Pawn*>(currPiece)->set_en_passant(false);
            }
    if (fromPiece->get_type() == PAWN and to.x == 2 + from.x)
        dynamic_cast<Pawn*>(fromPiece)->set_en_passant(true);

    std::swap(playerToMove, playerToWait);
    return currBoard->get_status();
}