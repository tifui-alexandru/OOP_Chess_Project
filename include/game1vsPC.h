#ifndef GAME1VSPC_H
#define GAME1VSPC_H
#include "gameFront.h"

class Game1vsPC : virtual public GameFront {
public:
    Game1vsPC();
    void play();
    void computerMove();
};

#endif // !GAME1VSPC_H