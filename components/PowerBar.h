#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
struct PowerBar{

    PowerBar(bool left_in){
        left = left_in;
        power = 30;
        up = true;

        temp.loadFromFile("sprite/power_bar.png");
        bar_sprite.setTexture(temp);
        bar_sprite.setScale(0.3, 0.3);
        
        scale.setSize(sf::Vector2f(30, 4));
        scale.setFillColor(sf::Color::Black);

        pCircle.setRadius(30);
        pCircle.setOrigin(pCircle.getGlobalBounds().width / 2, pCircle.getGlobalBounds().height / 2);
        pCircle.setFillColor(sf::Color::Red); 
        //pCircle.setOutlineThickness(3);
        pCircle.setOutlineColor(sf::Color::Black);

        //more points makes circle outline smoother 
        pCircle.setPointCount(1000);

        if (left){
            scale.setPosition(9.5, 171);
            bar_sprite.setPosition(15, 20);
            pCircle.setPosition(80, 40);

        }
        else{
            scale.setPosition(860.5, 171);
            bar_sprite.setPosition(885 - bar_sprite.getGlobalBounds().width, 20); 
            pCircle.setPosition(820, 40);                                                                        
        }
        
    }

    //add time input later

    void updateScale(){
        if (scale.getPosition().y == 171){
            up = true;
        }
        if (scale.getPosition().y == 21){
            up = false;

        }
        if (up){
            scale.setPosition(scale.getPosition().x, scale.getPosition().y - 0.5);
        }
        else{
            scale.setPosition(scale.getPosition().x, scale.getPosition().y + 0.5);
        }
        
    }

    //updates power level and circle radius
    void updatePower(){
        if (power <= 5){
            return;
        }
        power = power - 0.005;
        pCircle.setRadius(power);
        pCircle.setOrigin(pCircle.getGlobalBounds().width / 2, pCircle.getGlobalBounds().height / 2);
        if (left){
            pCircle.setPosition(80, 40);
        }
        else{
            pCircle.setPosition(820, 40);                                                                        
        }

    }

    void resetPower(){
        power = 30;
        pCircle.setRadius(30);
        pCircle.setOrigin(pCircle.getGlobalBounds().width / 2, pCircle.getGlobalBounds().height / 2);

        if (left){
            pCircle.setPosition(80, 40);

        }
        else{
            pCircle.setPosition(820, 40);                                                                        
        }

    }

    void draw(sf::RenderWindow &window){
        window.draw(bar_sprite);
        window.draw(scale);
        window.draw(pCircle);
    }

    //gets power of cannon
    int getPower(){

        //return 1000;
        return int(power / 1.2);
    }

    //gets power of shot
    int getShotPower(){
        return (std::abs(scale.getPosition().y - 171) / 150) * 50 + 30;
    
    }



    bool left;
    sf::Texture temp;
    sf::Sprite bar_sprite;

    //the moving bar part of the power bar
    sf::RectangleShape scale;

    //power circle that counts down
    sf::CircleShape pCircle;
    double power;

    //true if scale going up, false if scale going down
    bool up;
};