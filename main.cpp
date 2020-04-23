#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "src/MainMenu.cpp"
#include "src/GameMenu.cpp"
#include "src/game1v1.cpp"

int main()
{
    menuGame t1;
    menuMode t2;
    //t2.menuRun();
    Game1v1 t3;
    t3.playGame1v1();
//     do{
//        t1.menuRun();
//        if(t1.playButton == true) t2.menuRun();
//     }while(t1.terminate == false && t2.terminate == false;
    return 0;
}
