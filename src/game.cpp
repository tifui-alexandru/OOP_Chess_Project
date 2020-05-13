#include "../include/utils.h"
#include "../include/game.h"
#include <vector>
#include <iostream>

Game::Game() {
    resign = false;
    playerToMove = new Player(WHITE);
    playerToWait = new Player(BLACK);
    nrMovesFor50Rule = 0;
    gameBoards.push_back(new Board);
}

Game::~Game() {
    delete playerToMove;
    delete playerToWait;
    gameBoards.clear();
    gameMoves.clear();
}

Board* Game::get_board(int time) {
    // assert(time >= -1 && time < (int)gameBoards.size());
    if(time == -1) return gameBoards.back();
    return gameBoards[time];
}

void Game::promote(Square pos, PieceType piece) {
    auto oldPiece = gameBoards.back()->get_piece(pos);
    if (piece == QUEEN) gameBoards.back()->change_position(new Queen(oldPiece->get_colour(), pos), pos);
    else if (piece == ROOK) gameBoards.back()->change_position(new Rook(oldPiece->get_colour(), pos), pos);
    else if (piece == KNIGHT) gameBoards.back()->change_position(new Knight(oldPiece->get_colour(), pos), pos);
    else if (piece == BISHOP) gameBoards.back()->change_position(new Bishop(oldPiece->get_colour(), pos), pos);
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
                if ((piece1 == nullptr && piece2 == nullptr) or (piece1 != nullptr && piece2 != nullptr && piece1->get_type() == piece2->get_type() && piece1->get_colour() == piece2->get_colour())) continue;
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
    if (auto toPiece = currBoard->get_piece(to)) {
        playerToMove->capturedPieces.push_back(toPiece);
        playerToWait->pawnValue -= toPiece->get_value();
        nrMovesFor50Rule = 0;
    }
    else if (currBoard->get_piece(from)->get_type() == PAWN and to.y != from.y) { // en passant
        auto capturedPawn = currBoard->get_piece(from + Square(0, to.y - from.y));
        playerToMove->capturedPieces.push_back(capturedPawn);
        playerToWait->pawnValue -= 1;
        currBoard->change_position(nullptr, from + Square(0, to.y - from.y));
    }
    auto fromPiece = currBoard->get_piece(from);
    // if castling move the rook
    if (fromPiece->get_type() == KING and abs(from.y - to.y) == 2) {
        int add = (from.y < to.y ? 1 : -1);
        Square rookSquare = from;
        rookSquare.y = (add == 1 ? 7 : 0);
        auto rook = currBoard->get_piece(rookSquare);
        currBoard->change_position(rook, from + Square(0, add));
        currBoard->change_position(nullptr, rookSquare);
    }

    // handle en-passant
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (auto currPiece = currBoard->get_piece({i, j})) {
                if (currPiece->get_type() == PAWN and currPiece->get_colour() == playerToMove->colour)
                    dynamic_cast<Pawn*>(currPiece)->set_en_passant(false);
            }
    if (fromPiece->get_type() == PAWN and abs(from.x - to.x) == 2)
        dynamic_cast<Pawn*>(fromPiece)->set_en_passant(true);

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

GameStatus Game::get_status() {
    if (resign) return RESIGNATION;
    if (nrMovesFor50Rule == 50) return MOVE50RULE;
    if (repetition()) return REPETITION;
    return get_board()->get_status(playerToMove->colour, playerToWait->colour);
}

PieceColour Game::getPlayerToMove() {
    return playerToMove->colour;
}

void Game::set_resign()
{
    resign = true;
}