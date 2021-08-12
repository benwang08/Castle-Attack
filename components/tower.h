#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct tower
{
    tower(bool left_in):left(left_in){
        //initializing sprites with loaded texture
        //scaling sprite and setting position
        if (left){
            temp.loadFromFile("sprite/castle_left.png");
            tempdmg1.loadFromFile("sprite/castle_left_lightdmg.png");
            tempdmg2.loadFromFile("sprite/castle_left_heavydmg.png");
            fullSprite.setTexture(temp);
            fullSprite.setScale(0.40, 0.40);
            fullSprite.setPosition(0, 350);

            vertices.emplace_back(0,350);
            vertices.emplace_back(98, 470);
            vertices.emplace_back(98, 518);
        }
        else{
            temp.loadFromFile("sprite/castle_right.png");
            tempdmg1.loadFromFile("sprite/castle_right_lightdmg.png");
            tempdmg2.loadFromFile("sprite/castle_right_heavydmg.png");
            fullSprite.setTexture(temp);
            fullSprite.setScale(0.40, 0.40);
            fullSprite.setPosition(802, 350);

            vertices.emplace_back(900, 350);
            vertices.emplace_back(802, 470);
            vertices.emplace_back(802, 518);
        }

    }

    //draws tower sprite based on current health
    void draw(sf::RenderWindow &window){
        window.draw(fullSprite);
    }

    void update_tower(int health){
        if (health > 75){
            return;
        }
        else if (health >= 35 && health <= 75 ){
            fullSprite.setTexture(tempdmg1);
        }
        else{
            fullSprite.setTexture(tempdmg2);
        }
    }
    
    //returns true if coordinates collide with tower hitbox
    bool collide(float x, float y){
        // y value less than ground level
        if (y >= vertices[2].second){
            return false;
        }
        double slope = double(vertices[1].second - vertices[0].second) / (vertices[1].first - vertices[0].first);
        if (left){
            //return false if x value is not in range to prevent extra checks
            if (x > vertices[1].first){
                return false;
            }
            if (x <= vertices[1].first && y >= vertices[1].second){
                return true;
            }
            double yTest = slope * x + vertices[0].second;

            if (y >= yTest){
                return true;
            }
        }
        else{
            if (x < vertices[1].first){
                return false;
            }
            if (x >= vertices[1].first && y >= vertices[1].second){
                return true;
            }
            double yTest = slope * (x - vertices[0].first) + vertices[0].second;

            if (y >= yTest){
                return true;
            }
        }
        return false;
    }

    //"temporary" texture for purpose of initializing sprites
    //must be included in member variables due to lifespan
    sf::Texture temp;
    sf::Texture tempdmg1;
    sf::Texture tempdmg2;

    //true if left tower
    bool left;

    //vertices to detect collision, sprite represented in trapezoidal shape
    std::vector<std::pair<int, int>> vertices;
    sf::Sprite fullSprite;
};
