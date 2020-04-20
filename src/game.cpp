#include "../include/utils.h"
#include "../include/game.h"
#include <vector>
#include <algorithm>

Game::Game() {
    playerToMove->Colour = WHITE;
    playerToWait->Colour = BLACK;
    gameBoards.push_back(new Board);
}

Board* Game::get_board(int time) {
    assert(time >= -1 && time < gameBoards.size());
    if(time == -1) return gameBoards.back();
    return gameBoards[time];
}

void Game::make_move(Square from, Square to) {
    auto currBoard = new Board(gameBoards.back());
    if(auto toPiece = currBoard->get_piece(to)) {
        playerToMove->capturedPieces.push_back(toPiece);
        playerToWait->pawnValue -= toPiece->get_value();
    }
    auto fromPiece = currBoard->get_piece(from);
    fromPiece->inc_no_moves();
    currBoard->change_position(fromPiece, to);
    currBoard->change_position(nullptr, from);
    gameBoards.push_back(currBoard);
    std::swap(playerToMove, playerToWait);
}