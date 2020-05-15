#include "include/startGame.h"

int main()
{
    auto newGame = startGame::GetInstance();
    newGame->runStart();
    return 0;
}
