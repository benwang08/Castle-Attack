#include <SFML/Graphics.hpp>

struct ball
{

    ball(){
        temp.loadFromFile("sprite/ball.png");
        ball_sprite.setTexture(temp);
        ball_sprite.setScale(0.05, 0.05);

        explosionTemp.loadFromFile("sprite/explosion.png");
        explosion.setTexture(explosionTemp);
        explosion.setScale(0.2, 0.2);

    }

    void set_position(int x, int y){
        ball_sprite.setPosition(x, y);
    }

    int getX(){
        return ball_sprite.getPosition().x;
    }

    int getY(){
        return ball_sprite.getPosition().y;
    }

    //function takes in current ball position and magnitude in x and y directions
    //will redraw ball in new position and return updated y magnitude after applying "gravity"
    // 0 <= x_mag, y_mag, <= 100
    float update(float x_mag, float y_mag){
        y_mag = y_mag - 0.06;

        ball_sprite.setPosition(ball_sprite.getPosition().x + x_mag / 100, 
        ball_sprite.getPosition().y - y_mag / 100);

        return y_mag;
    }
    void draw(sf::RenderWindow &window){
        window.draw(ball_sprite);
    }


    //animate explosion using sprite sheet, each sub-image is 256x256
    //frame starts at 0
    void update_explosion(int frame){
        float x = ball_sprite.getPosition().x;
        float y = ball_sprite.getPosition().y;

        //x and y position on sheet, 0 indexed from top left corner
        int sheetX = (frame % 8);
        int sheetY = (frame / 8);

        int xPixel = sheetX * 256;
        int yPixel = sheetY * 256;

        explosion.setTextureRect(sf::Rect<int>(xPixel, yPixel, 256, 256));
        explosion.setPosition(x - explosion.getGlobalBounds().width / 2, y - explosion.getGlobalBounds().height / 2);
        
    }

    void draw_explosion(sf::RenderWindow &window, int frame){
        update_explosion(frame);
        window.draw(explosion);
    }
    


    sf::Sprite ball_sprite;
    sf::Texture temp;

    sf::Sprite explosion;
    sf::Texture explosionTemp;

};
