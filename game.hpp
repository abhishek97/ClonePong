#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

class Game{

    bool playing;

    bool pocketed;

public:

    int score_p1;
    int score_p2;

    Game()
    {
        playing = false;
        pocketed = false;
        score_p1 = score_p2 = 0;

    }
    bool isPlaying()
    {
        return playing;
    }

    bool isPocketed()
    {
        return pocketed;
    }

    void pocket()
    {
        pocketed = true;
    }

    void reset_pocket()
    {
        pocketed = false;
    }

    void setPlaying(bool val)
    {
        playing = val;
    }


};


class player{

sf::RectangleShape plate;


public:
    int speed ;
    player(sf::Vector2f size , int x, int y )
    {
        plate.setSize(size);
        plate.setPosition(x,y);
        speed =0;
    }

    sf::RectangleShape getPlate()
    {
        return plate;
    }

    void move()
    {
        if( speed > 0  && plate.getPosition().y > 550)
            return ;

        if( speed < 0 && plate.getPosition().y < 5 )
            return ;

        plate.move( 0 , speed);
    }

    void setPosition(int x, int y)
    {
        plate.setPosition(x,y);
    }

};


class ball{

sf::CircleShape token;

public:
    int speed_x, speed_y;

    ball(int x, int y , int rad)
    {
        token.setRadius(rad);
        token.setPosition(x,y);
        speed_x = -5;
        speed_y = 5;
    }

    void move()
    {
        if( token.getPosition().y <= 5 || token.getPosition().y >= 580 )
            {
                if(std::abs(speed_y) < 10)
                    speed_y *= -1.1;
                else
                    speed_y *= -1;
            }

        token.move(speed_x  , speed_y); // Currently no acceleration
    }

    sf::CircleShape getBall()
    {
        return token;
    }

    bool collides_with(sf::RectangleShape plate)
    {
       sf::FloatRect self_bounds = token.getGlobalBounds();
       sf::FloatRect bounds = plate.getGlobalBounds();

        if(bounds.intersects(self_bounds) )
            return true;
        else
            return false;
    }

    int out_of_frame()
    {
        if(token.getPosition().x <= 0 )
            return 1;                           // 1 score for player 2
        else if(token.getPosition().x >= 800 )
           return -1;                           // -1 score for player 1
        else
            return 0;
    }


};

class menuItem{

    sf::Text text;
    sf::RectangleShape box;
    bool active;

public:
     std::string action;
    menuItem(sf::Font &font)
    {
        text.setFont(font);
        text.setCharacterSize(50);
        active = false;
    }

    void set_active()
    {
        active = true;
        text.setColor(sf::Color::Red);
    }

    void rm_active()
    {
        active = false;
        text.setColor(sf::Color::White);
    }

    void setText(std::string s)
    {
        text.setString(s);
    }

    void setPosition(int x, int y)
    {
        text.setPosition(x,y);

        box.setSize(sf::Vector2f( 105 , 80 ));
        box.setPosition(x,y);
        box.setOutlineThickness(5);
        box.setOutlineColor(sf::Color::Blue);
        box.setFillColor(sf::Color::Black);
    }


    bool isActive()
    {
        return active;
    }

    sf::Text getText()
    {
        return text;
    }
    sf::RectangleShape getBox()
    {
        return box;
    }


};


#endif // GAME_HPP_INCLUDED
