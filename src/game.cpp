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
    auto fromPiece = currBoard->get_piece(from);
    fromPiece->inc_no_moves();
    currBoard->change_position(fromPiece, to);
    currBoard->change_position(nullptr, from);
    gameMoves.push_back(new Move(from, to, gameBoards.back(), currBoard, playerToMove->colour));
    gameBoards.push_back(currBoard);
    std::swap(playerToMove, playerToWait);
    return currBoard->get_status();
}