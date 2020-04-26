#ifndef GAME1VSPC_H
#define GAME1VSPC_H
#include "gameFront.h"

class Game1vsPC : virtual public GameFront {
private:
    PieceColour humanPlayer;
public:
    Game1vsPC(const PieceColour &humanCol = WHITE);
    void play();
};

#endif // !GAME1VSPC_H