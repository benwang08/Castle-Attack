#include <SFML/Graphics.hpp>

struct health{

    health(bool left_in) : left(left_in){
        bar.setSize(sf::Vector2f(100, 8));
        bar.setFillColor(sf::Color::Green);
        if (left){
            bar.setPosition(0, 525);
        }
        else{
            bar.setPosition(800, 525);
        }
        hp = 100;
    }

    

    void draw(sf::RenderWindow &window){
        bar.setSize(sf::Vector2f(hp, 8));
        //need to move right hp bar after updating hp
        if (!left){
            bar.setPosition(900 - hp, 525);
        }
        if (hp >= 35 && hp <= 75){
            bar.setFillColor(sf::Color::Yellow);
        }
        if (hp < 35){
            bar.setFillColor(sf::Color::Red);
        }
        window.draw(bar);
    }

    void setHealth(int in){
        hp = in;
    }

    int getHealth(){
        return hp;
    }


    //health bar represented by rectangle shape
    sf::RectangleShape bar;
    bool left;
    int hp;
    
};