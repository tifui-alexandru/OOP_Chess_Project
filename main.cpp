#include "include/startGame.h"

int main()
{
    auto newGame = startGame::GetInstance();
    try{
        newGame->runStart();
    } catch(Exception &e) {
        std::cerr << e.what();
    }
    return 0;
}
