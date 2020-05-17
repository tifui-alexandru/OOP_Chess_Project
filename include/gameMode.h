#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "game1vsPC.h"
#include "game1vs1.h"


class GameMode {
private:
    std::unique_ptr<GameFront> strategy;
    //GameFront* strategy;
public:
    enum StrategyType {
        _1VS1, _1VSPC
    };
    GameMode() {
        strategy = nullptr;
    }
    void setStrategy(StrategyType type) {
        if (type == _1VS1) strategy = std::make_unique<Game1vs1>();
        else if (type == _1VSPC) strategy = std::make_unique<Game1vsPC>();
    }
    void play() {
        strategy->play();
    }
};

#endif //CHESS_GAMEMODE_H
