#include "../include/game1vsPC.h"
#include <string>
#include <cstdlib>
#include <array>
#include <assert.h>

Game1vsPC::Game1vsPC(const PieceColour &humanCol) {
    GameFront();
    humanPlayer = humanCol;
}

std::string get_system(const char* command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::pair <Square, Square> getStockfishMove(const std::string& currBoardPosition) {
    std::string command = "position startpos";
    if (!currBoardPosition.empty()) command += " moves " + currBoardPosition;

    assert(system(command.c_str()));
    std::string temp = get_system("go");
    
    size_t pos = temp.find("bestmove");
    while (temp[pos] != ' ') ++pos;
    while (temp[pos] == ' ') ++pos;

    std::string from, to;
    from = temp[pos] + temp[pos + 1];
    to = temp[pos + 2] + temp[pos + 3];

    return std::make_pair(my_notation_pos(from), my_notation_pos(to));
}

void Game1vsPC::play() {
    int noCurrMoves = 0;
    PieceColour playerMoving = WHITE;
    std::string currBoardPosition;

    // initialize stockfish
    assert(system("./stockfish"));
    assert(system("ucinewgame"));
    assert(get_system("isready") == "readyok");

    while(window.isOpen()) {
        window.clear();

        if (playerMoving == humanPlayer) {
            EventType event = checkClick();
            if (event == BOARD_CLICK) {
                squareClicked();
            }
        }
        else {
            std::pair <Square, Square> computerMove = getStockfishMove(currBoardPosition);
            game->make_move(computerMove.first, computerMove.second);
        }

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here
            
            currBoardPosition += mv->toLongAlgebraicNotation() + " ";
            playerMoving = (playerMoving == WHITE ? BLACK : WHITE);

            printBoard(); // print cu butoane si chestii
        }

        if (game->get_status() != UNFINISHED) {
            // end of the game
            // display chestii
        }

        window.display();
    }
}
