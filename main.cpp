 #include <bits/stdc++.h>
 #include <SFML/Graphics.hpp>
 using namespace sf;

 class img
 {

     // the images we will use for the windows

 public:

     Texture t;
     Sprite s;

 public:

     img(std::string path)
     {

         //search for the images

         t.loadFromFile(path);

         s.setTexture(t);
     }
 };

 int main()
 {
     RenderWindow window(sf::VideoMode(680, 544), "MENU", sf::Style::Titlebar | sf::Style::Close);
     // VideoMode - > window size
     // "MENU" -> window title
     // style -> can not be resizable

     img usu1("../images/menu_img.jpg");

     Vector2u size = usu1.t.getSize();

     img usu2("../images/play1.png");

     img usu3("../images/play2.png");

     img usu4("../images/about1.png");

     img usu5("../images/about2.png");

     while (window.isOpen())
     {

         sf::Event event;

         while (window.pollEvent(event))
         {

             //until we close the window

             if (event.type == sf::Event::Closed)
                 window.close();
         }

         Vector2i pos = Mouse::getPosition(window);

         //get the position every time to know where the mouse is

         usu2.s.setPosition(207.5, 120);

         usu3.s.setPosition(207.5, 120);

         usu4.s.setPosition(250, 400);

         usu5.s.setPosition(250, 400);

         window.clear();
         //refresh

         window.draw(usu1.s);

         //change the play button
         if(pos.x >= 207.5 && pos.x<= 207.5 + 265 && pos.y >= 120 && pos.y <= 120 + 121)
             window.draw(usu3.s);

         else
             window.draw(usu2.s);

         //change the about button
         if(pos.x >= 207.5 && pos.x<= 207.5 + 180 && pos.y >= 400 && pos.y <= 400 + 83)
             window.draw(usu5.s);

         else
             window.draw(usu4.s);

         window.display();

     }

     return 0;
 }
