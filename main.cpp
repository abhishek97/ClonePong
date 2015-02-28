#include <SFML/Graphics.hpp>
#include <game.hpp>
#include <iostream>
#include <stdlib.h>


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "PANG!");


    Game pang;
    sf::Font font;

    if(!font.loadFromFile("Lobster.otf"))
    {
        std::cout<<"Font was not loaded/found.";
    }

    sf::Text score_name;
    sf::Text score;
    std::vector<menuItem> menu;

    score_name.setFont(font);
    score_name.setString("Score");
    score_name.setCharacterSize(70);
    score_name.setPosition(325,30);


    score = score_name;
    score.setCharacterSize(50);

    score.setString("0 - 0");
    score.setPosition(350,100);

    bool aiMove = false;




    while(window.isOpen() )
{


    if(!pang.isPlaying())
    {
        sf::Text Header;

        Header.setFont(font);
        Header.setString("PONG !");
        Header.setColor(sf::Color::Yellow);
        Header.setPosition(250 , 50);
        Header.setCharacterSize(100);

        menuItem play_button(font);
        play_button.set_active();
        menuItem exit_button(font);
        play_button.setText("Play");
        play_button.setPosition(320, 250);
        play_button.action = "play";
        exit_button.setText("Exit !");
        exit_button.action = "exit";
        exit_button.setPosition(320, 350);





        while(window.isOpen() && !pang.isPlaying())
        {
             sf::Event event;

             while(window.pollEvent(event))
             {
                  if (event.type == sf::Event::Closed)
                        window.close();

                    if(event.type == sf::Event::KeyPressed)
                    {
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        {
                            if(play_button.isActive())
                                pang.setPlaying(true);
                            else
                                window.close();
                        }

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        {
                            if(play_button.isActive())
                                {
                                    play_button.rm_active();
                                    exit_button.set_active();
                                }
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        {
                            if(exit_button.isActive())
                                {
                                    exit_button.rm_active();
                                    play_button.set_active();
                                }
                        }


                    }

             }

        window.clear(sf::Color::Black);
        window.draw(play_button.getText());
        window.draw(play_button.getBox());
        window.draw(play_button.getText());
        window.draw(exit_button.getBox());
        window.draw(exit_button.getText());
        window.draw(Header);

        window.display();


        }

    }


    aiMove = false;
    player p1(sf::Vector2f(10,80) , 0 , 300 );
    player p2(sf::Vector2f(10,80), 790 , 300);
    ball hit(300,300 , 10);

    hit.speed_x = (rand() % 5 + 1) * -1;
    hit.speed_y = rand() % 5 + 1;

    pang.reset_pocket();

	// Start the game loop
    while (window.isOpen() && !pang.isPocketed() && pang.isPlaying())
    {
       // p1.speed = 0;
      //  p2.speed = 0;
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();


            if(event.type == sf::Event::MouseMoved )
            {
                if( sf::Mouse::getPosition(window).y <= 550)
                p1.setPosition( p1.getPlate().getPosition().x , sf::Mouse::getPosition(window).y);
            }


           if(event.type == sf::Event::KeyPressed )
           {

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        p2.speed = 30;
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        p2.speed = -30;

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        pang.setPlaying(false);
           }



        }

        p1.move();
        p2.move();
        hit.move();

        if(aiMove)
            p2.speed = hit.speed_y;
        else if(hit.speed_y > 0)
            p2.speed = 10;
        else
            p2.speed = -10;

        if(hit.collides_with(p1.getPlate()) || hit.collides_with(p2.getPlate()))
        {

            //Shoot up the AI to change p2 speed...



            if(hit.collides_with(p1.getPlate()))
                aiMove = true;

            if(hit.collides_with(p2.getPlate()))
                aiMove = false;

            hit.speed_x = hit.speed_x >0 ? -8 : 8;
            hit.speed_x += p1.speed;
        }


        if(hit.out_of_frame())
        {
            if( hit.out_of_frame() == 1 )
                pang.score_p2++;
            else
                pang.score_p1++;

            std::string score_str;
            score_str = " " + std::to_string(pang.score_p1) + " - " + std::to_string(pang.score_p2) + " ";

            score.setString(score_str);
            pang.pocket();
        }



        // Clear screen
        window.clear();

        window.draw(p1.getPlate());

        window.draw(hit.getBall());

        window.draw(p2.getPlate());
        window.draw(score_name);
        window.draw(score);



        // Update the window
        window.display();
    }

}

    return EXIT_SUCCESS;
}
