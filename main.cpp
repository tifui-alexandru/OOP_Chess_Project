#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "include/MainMenu.h"
#include "include/GameMenu.h"
#include "include/game1vs1.h"
#include "include/about.h"

int main()
{
    //menuAbout t;
    //t.menuRun();

    menuGame t1;
    menuMode t2;
    Game1vs1 t3;
    menuAbout t4;

    bool menuModeGo = false;
    bool Game1v1Go = false;
    bool menuAboutGo = false;

    t3.play();

//    do{
//        if(menuGameGo == true)
//        {
//            t1.menuRun();
//            menuGameGo = false;
//
//            if(t1.menuModeGo == true)
//            {
//                t1.menuModeGo = false;
//                menuModeGo = true;
//            }
//
//            if(t1.menuAboutGo == true)
//            {
//                t1.menuAboutGo = false;
//                menuAboutGo = true;
//            }
//        }
//
//        if(menuModeGo == true)
//        {
//            t2.menuRun();
//            menuModeGo = false;
//
//            if(t2.Game1v1Go == true)
//            {
//                t2.Game1v1Go = false;
//                Game1v1Go = true;
//            }
//
//            if(t2.menuGameGo == true)
//            {
//                t2.menuGameGo = false;
//                menuGameGo = true;
//            }
//        }
//
//        if(Game1v1Go == true)
//        {
//            t3.playGame1v1();
//            Game1v1Go = false;
//        }
//
//        if(menuAboutGo == true)
//        {
//            t4.menuRun();
//            menuAboutGo = false;
//
//            if(t4.menuGameGo == true)
//            {
//                t4.menuGameGo = false;
//                menuGameGo = true;
//            }
//        }
//
//
//     }while(t1.terminate == false && t2.terminate == false && t3.terminate == false && t4.terminate == false);

    return 0;
}
