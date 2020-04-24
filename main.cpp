#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "include/MainMenu.h"
#include "include/GameMenu.h"
#include "include/game1v1.h"
//#include "src/about.cpp"

int main()
{
    //menuAbout t;
    //t.menuRun();

    menuGame t1;
    menuMode t2;
    Game1v1 t3;

    bool menuGameGo = true;
    bool menuModeGo = false;
    bool Game1v1Go = false;

    do{
        if(menuGameGo == true)
        {
            t1.menuRun();
            menuGameGo = false;

            if(t1.menuModeGo == true)
            {
                t1.menuModeGo = false;
                menuModeGo = true;
            }
        }

        if(menuModeGo == true)
        {
            t2.menuRun();
            menuModeGo = false;

            if(t2.Game1v1Go == true)
            {
                t2.Game1v1Go = false;
                Game1v1Go = true;
            }

            if(t2.menuGameGo == true)
            {
                t2.menuGameGo = false;
                menuGameGo = true;
            }
        }

        if(Game1v1Go == true)
        {
            t3.playGame1v1();
            Game1v1Go = false;
        }


     }while(t1.terminate == false && t2.terminate == false && t3.terminate == false);

    return 0;
}
