#include "../include/utils.h"
#include "../include/game.h"
#include <vector>

Game::Game() {
    playerToMove = new Player(WHITE);
    playerToWait = new Player(BLACK);
    nrMovesFor50Rule = 0;
    gameBoards.push_back(new Board);
}

Board* Game::get_board(int time) {
    assert(time >= -1 && time < gameBoards.size());
    if(time == -1) return gameBoards.back();
    return gameBoards[time];
}

bool Game::repetition() {
    int cntBoard = 0;
    auto currBoard = gameBoards.back();
    for (auto board : gameBoards) {
        int equal = 1;
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j) {
                auto piece1 = currBoard->get_piece({i, j});
                auto piece2 = board->get_piece({i, j});
                if ((piece1 == nullptr && piece2 == nullptr) or (piece1 != nullptr && piece2 !=nullptr && piece1->get_type() == piece2->get_type())) continue;
                equal = 0;
                break;
            }
        cntBoard += equal;
    }
    return cntBoard >= 3;
}

GameStatus Game::make_move(Square from, Square to) {
    auto currBoard = new Board(gameBoards.back());
    nrMovesFor50Rule++;
    if(auto toPiece = currBoard->get_piece(to)) {
        playerToMove->capturedPieces.push_back(toPiece);
        playerToWait->pawnValue -= toPiece->get_value();
        nrMovesFor50Rule = 0;
    }
    auto fromPiece = currBoard->get_piece(from);
    if (fromPiece->get_type() == PAWN) nrMovesFor50Rule = 0;
    fromPiece->inc_no_moves();
    currBoard->change_position(fromPiece, to);
    currBoard->change_position(nullptr, from);
    gameMoves.push_back(new Move(from, to, gameBoards.back(), currBoard, playerToMove->colour));
    gameBoards.push_back(currBoard);
    std::swap(playerToMove, playerToWait);
    if (nrMovesFor50Rule == 50) return MOVE50RULE;
    if (repetition()) return REPETITION;
    return currBoard->get_status(playerToMove->colour, playerToWait->colour);
}