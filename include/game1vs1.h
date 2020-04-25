#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {
public:
    Game1vs1();
    void play();
};

#endif // !GAME1VS1_H