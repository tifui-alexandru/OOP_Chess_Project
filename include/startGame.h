#ifndef STARTGAME_H
#define STARTGAME_H

#include "MainMenu.h"
#include "GameMenu.h"
#include "game1vs1.h"
#include "about.h"
#include "game1vsPC.h"


class startGame
{
    startGame();

    startGame & operator= (const startGame & ) = delete;
    static startGame * instance_;
public:
    static startGame * GetInstance();
    static void runStart();
};


#endif //CHESS_STARTGAME_H
