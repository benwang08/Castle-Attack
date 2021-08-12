#include <SFML/Graphics.hpp>
#include <iostream>
struct cannon
{
    //helper function that changes origin while mainting original position
    void setOriginAndReadjust(sf::Transformable &object, const sf::Vector2f &newOrigin){
        auto offset = newOrigin - object.getOrigin();
        object.setOrigin(newOrigin);
        object.move(offset);
    }

    cannon(bool left_in) : angle(0), left(left_in){

        if (left){
            temp.loadFromFile("sprite/cannon.png");
            cannon_sprite.setTexture(temp);
            cannon_sprite.setPosition(35, 415);
            setOriginAndReadjust(cannon_sprite, sf::Vector2f(12, 18));
        }
        else{
            temp.loadFromFile("sprite/cannon_flip.png");
            cannon_sprite.setTexture(temp);
            cannon_sprite.setPosition(865 - cannon_sprite.getGlobalBounds().width, 415);
            setOriginAndReadjust(cannon_sprite, sf::Vector2f((cannon_sprite.getGlobalBounds().width - 12), 18));

        }
    }

    void draw(sf::RenderWindow &window){
        // displaying origin for debugging purposes
        // sf::CircleShape test;
        // test.setRadius(2);
        // test.setPosition(cannon_sprite.getOrigin().x, cannon_sprite.getOrigin().y);
        // test.setFillColor(sf::Color::Red);
        // window.draw(test);
        
        window.draw(cannon_sprite);
    }

    void angle_up(float add){
        if (angle > 90){
            return;
        }
        angle += add;
        if (left){
            cannon_sprite.setRotation(-1 * angle);
        }
        else{
            cannon_sprite.setRotation(angle);
        }
    }

    void angle_down(float minus){
        if (angle < 0){
            return;
        }
        angle -= minus;
        if (left){
            cannon_sprite.setRotation(-1 * angle);
        }
        else{
            cannon_sprite.setRotation(angle);
        }
    }
    void reset(){
        angle = 0;
        cannon_sprite.setRotation(angle);
    }

    int getAngle(){
        return angle;
    }



    //cannon angle and cannon side
    int angle;
    bool left;

    sf::Texture temp;
    sf::Sprite cannon_sprite;
};
