#include "../include/startGame.h"

void startGame::runStart()
{
    menuGame t1;
    menuMode t2;
    menuAbout t4;


    bool menuModeGo = false;
    bool menuGameGo = true;
    bool menuAboutGo = false;
    bool Game1v1Go = false;
    bool Game1vPcGo = false;

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

            if(t1.menuAboutGo == true)
            {
                t1.menuAboutGo = false;
                menuAboutGo = true;
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

            if(t2.Game1vPcGo == true)
            {
                t2.Game1vPcGo = false;
                Game1vPcGo = true;
            }

            if(t2.menuGameGo == true)
            {
                t2.menuGameGo = false;
                menuGameGo = true;
            }
        }

        if(Game1v1Go == true)
        {
            Game1vs1 t3;
            t3.play();
            Game1v1Go = false;
            menuModeGo = true;
        }

        if(Game1vPcGo == true)
        {
            Game1vsPC t5;
            t5.play();
            Game1vPcGo = false;
            menuModeGo = true;
        }

        if(menuAboutGo == true)
        {
            t4.menuRun();
            menuAboutGo = false;

            if(t4.menuGameGo == true)
            {
                t4.menuGameGo = false;
                menuGameGo = true;
            }
        }


     }while(menuModeGo == true || menuGameGo == true || menuAboutGo == true || Game1v1Go == true);
}