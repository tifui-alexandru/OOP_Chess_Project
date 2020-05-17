#include "../include/utils.h"
#include "../include/board.h"

Board::Board() {
    board.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i)
        board[i].resize(BOARD_SIZE, nullptr);
    for (auto colour : {WHITE, BLACK}) {
        int row = 0, offset = 1;
        if (colour == BLACK) row =  7, offset = -1;
        board[row][0] = Piece::createPiece(ROOK, colour, {row, 0});
        board[row][7] = Piece::createPiece(ROOK, colour, {row, 7});
        board[row][1] = Piece::createPiece(KNIGHT, colour, {row, 1});
        board[row][6] = Piece::createPiece(KNIGHT, colour, {row, 6});
        board[row][2] = Piece::createPiece(BISHOP, colour, {row, 2});
        board[row][5] = Piece::createPiece(BISHOP, colour, {row, 5});
        board[row][3] = Piece::createPiece(QUEEN, colour, {row, 3});
        board[row][4] = Piece::createPiece(KING, colour, {row, 4});

        for (int col = 0; col < 8; ++col)
            board[row + offset][col] = Piece::createPiece(PAWN, colour, {row + offset, col});
    }
}

Board::Board(const Board *obj) {
    board.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i)
        board[i].resize(BOARD_SIZE, nullptr);
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (auto piece = obj->get_piece({i, j})) board[i][j] = piece->Clone();
}

Board::~Board() {
    for (auto& it : board)
        for(auto& itt: it)
            delete itt;
    board.clear();
}

void Board::change_position(Piece* newPiece, Square pos) {
    board[pos.x][pos.y] = newPiece;
    if (newPiece) newPiece->set_position(pos);
}

Piece* Board::get_piece(Square pos) const {
    return board[pos.x][pos.y];
}

Square Board::get_king(const PieceColour &colour) const {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == nullptr) continue;
            if (board[i][j]->get_type() == KING and board[i][j]->get_colour() == colour) return {i, j};
        }
    return {-1,-1};
}

/// verify if a cell is attacked by the opponent
bool Board::cell_is_attacked(Square pos, PieceColour colour) const {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == nullptr or board[i][j]->get_colour() == colour) continue;
            auto positions = board[i][j]->get_possible_moves(board);
            for (auto p : positions)
                if (p == pos) return true;
        }
    return false;
}

bool Board::castle(const PieceColour &colour, const CastleType &tp) const {
    int row = (colour == WHITE ? 0 : 7);
    int king_col = 4;
    int rook_col = (tp == QUEENSIDE ? 0 : 7);

    if (board[row][king_col] == nullptr or board[row][rook_col] == nullptr) return false;
    if (board[row][king_col]->get_type() != KING or board[row][rook_col]->get_type() != ROOK) return false;
    if (board[row][king_col]->moved() or board[row][rook_col]->moved()) return false;

    if (cell_is_attacked(Square(row, king_col), colour)) return false; 

    int add = (rook_col - king_col) / std::abs(rook_col - king_col);
    for (int step = 0, col = king_col + add; step < 2; col += add, ++step) {
        if (board[row][col] != nullptr) return false;
        if (cell_is_attacked(Square(row, col), colour)) return false;
    }

    return true;
}

/// returns the valid moves for the piece from a given square
std::vector<Square> Board::get_valid_moves(Square pos, PieceColour colour) {
    if (board[pos.x][pos.y] == nullptr or board[pos.x][pos.y]->get_colour() != colour) return {};
    auto positions = board[pos.x][pos.y]->get_possible_moves(board);
    std::vector<Square> valid_positions;
    for (auto p : positions) {
        auto aux = board[p.x][p.y];
        board[p.x][p.y] = board[pos.x][pos.y];
        board[pos.x][pos.y] = nullptr;
        if (!cell_is_attacked(get_king(colour), colour)) valid_positions.push_back(p);
        board[pos.x][pos.y] = board[p.x][p.y];
        board[p.x][p.y] = aux;
    }

    if (board[pos.x][pos.y]->get_type() == KING) {
        if (castle(colour, QUEENSIDE)) valid_positions.push_back(pos + Square(0, -2));
        if (castle(colour, KINGSIDE)) valid_positions.push_back(pos + Square(0, 2));
    }

    return valid_positions;
}

bool Board::insufficient_material(const PieceColour &colour) {
    int cnt = 0, cntKnight = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == nullptr or board[i][j]->get_colour() != colour or board[i][j]->get_type() == KING) continue;
            if (board[i][j]->get_type() == BISHOP) cnt++;
            if (board[i][j]->get_type() == KNIGHT) cnt++, cntKnight++;
            else return false;
        }
    if (cnt == 2 && cntKnight == 2) return true;
    return cnt <= 1;
}

GameStatus Board::get_status(const PieceColour &colourToMove, const PieceColour &colourToWait) {
    bool possibleMoves = false;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
                if (!get_valid_moves({i, j}, colourToMove).empty()) possibleMoves = true;
    bool check = cell_is_attacked(get_king(colourToMove), colourToMove);
    if (!possibleMoves && check) return CHECKMATE;
    if (!possibleMoves) return STALEMATE;
    if (insufficient_material(colourToMove) && insufficient_material(colourToWait)) return INSUFFICIENT_MATERIAL;
    return UNFINISHED;
}

bool Board::operator == (const Board &other) {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece1 = other.board[i][j];
            auto piece2 = board[i][j];
            if ((piece1 == nullptr && piece2 == nullptr) or (piece1 != nullptr && piece2 != nullptr && piece1->get_type() == piece2->get_type() && piece1->get_colour() == piece2->get_colour())) continue;
            return false;
        }
    return true;
}
