#include <SFML/Graphics.hpp>
#include <string>

struct sky{
    sky(){
        temp.loadFromFile("sprite/sky_background.png");
        background.setTexture(temp);
        background.setScale(1.5, 1.2);

        wind_temp.loadFromFile("sprite/wind.png");
        wind.setTexture(wind_temp);
        wind.setScale(0.3, 0.3);
        wind.setPosition(400, 10);
        //bool flipped keeps track of wind sprite direction
        flipped = false;
        
        windFont.loadFromFile("sprite/font.ttf");
        windText.setFont(windFont);
        windText.setCharacterSize(20);
        windText.setFillColor(sf::Color::Black);
        windText.setPosition(420,60);
        

        clouds_temp[0].loadFromFile("sprite/cloud1.PNG");
        clouds_temp[1].loadFromFile("sprite/cloud2.PNG");
        clouds_temp[2].loadFromFile("sprite/cloud3.PNG");

        clouds[0].setTexture(clouds_temp[0]);
        clouds[1].setTexture(clouds_temp[1]);
        clouds[2].setTexture(clouds_temp[2]);
        clouds[3].setTexture(clouds_temp[1]);
        clouds[4].setTexture(clouds_temp[0]);

        //making clouds different sizes
        clouds[0].setScale(0.5, 0.4);
        clouds[1].setScale(0.2, 0.2);
        clouds[2].setScale(0.6, 0.6);
        clouds[3].setScale(0.4, 0.3);
        clouds[4].setScale(0.3, 0.3);

        clouds[0].setPosition(-2, 200);
        clouds[1].setPosition(200, 4);
        clouds[2].setPosition(900, 0);
        clouds[3].setPosition(700, 50);
        clouds[4].setPosition(10, 20);

        groundTemp.loadFromFile("sprite/ground.png");
        ground.setTexture(groundTemp);
        ground.setScale(1, 0.8);
        ground.setPosition(0, 510);


        transition.setSize(sf::Vector2f(900, 600));
        transition.setFillColor(sf::Color(0,0,0,0));
        phase = 1;
        transparency = 0;

    }

    int getWind(){
        return windVal;
    }
    
    //updates clouds position to "animate"
    //smaller clouds move faster
    void update(){
        if (windVal == 0){
            return;
        }

        //change cloud directions based on wind direction
        int dir = 1;
        if (windVal < 0){
            dir = -1;
        }
        clouds[0].setPosition(double(clouds[0].getPosition().x) + dir * 0.13, clouds[0].getPosition().y);
        clouds[1].setPosition(double(clouds[1].getPosition().x) + dir * 0.45, clouds[1].getPosition().y);
        clouds[2].setPosition(double(clouds[2].getPosition().x) + dir * 0.15, clouds[2].getPosition().y);
        clouds[3].setPosition(double(clouds[3].getPosition().x) + dir * 0.28, clouds[3].getPosition().y);
        clouds[4].setPosition(double(clouds[4].getPosition().x) + dir * 0.18, clouds[4].getPosition().y);

        //wrap clouds around to other side if they're out of frame
        for(int i = 1; i < 5; i++){
            if (dir == 1){
                if (clouds[i].getPosition().x > 900){
                    if (i == 1){
                        clouds[i].setPosition(-10 - clouds[i].getGlobalBounds().width, std::rand() % 250);
                    }
                    else{
                        clouds[i].setPosition(0 - clouds[i].getGlobalBounds().width, std::rand() % 250);
                    }
                }
            }
            else{
                if (clouds[i].getPosition().x < -2 - clouds[i].getGlobalBounds().width){
                    if (i == 1){
                        clouds[i].setPosition(910, std::rand() % 250);
                    }
                    else{
                        clouds[i].setPosition(900, std::rand() % 250);
                    }
                }
            }

        }

    }

    void updateWind(){
        windVal = std::rand() % 15;
        
        //determine random wind direction (left or right)
        int direction = std::rand() % 2;
        if (direction == 0){
            windVal *= -1;
        }

        windText.setString(std::to_string(windVal));

    }

    void draw(sf::RenderWindow &window){
        window.draw(background);

        for(int i = 0; i < 5; i++){
            window.draw(clouds[i]);
        }
        
        //flipping wind sprite direction based on wind
        // if (windVal < 0 && !flipped){
        //     wind.setScale(-0.3, 0.3);
        //     wind.setPosition(462, 10);
        //     flipped = true;
        // }

        // if (windVal >= 0 && flipped){
        //     wind.setScale(-0.3, 0.3);
        //     wind.setPosition(400, 10);
        // }

        window.draw(wind);
        
        //center windSpeed text with wind cloud sprite
        // if (windVal >= 0){
        //     windText.setPosition((wind.getGlobalBounds().width / 2 + wind.getPosition().x) - (windText.getGlobalBounds().width / 2), 60);
        // }
        // else{
        //     windText.setPosition((wind.getGlobalBounds().width / -2 + wind.getPosition().x) - (windText.getGlobalBounds().width / 2) - 5, 60);
        // }

        windText.setPosition((wind.getGlobalBounds().width / 2 + wind.getPosition().x) - (windText.getGlobalBounds().width / 2), 60);
        
        window.draw(windText);
        window.draw(ground);

    }

    //returns '1' not done, '2' fully dark, '3'done
    int update_transition(){
        if (phase == 1){
            transparency += 0.5;
            transition.setFillColor(sf::Color(0,0,0, transparency));
            //std::cout << transparency << " ";
            if (transparency >= 250.0){
                phase = 2;
                return 2;
            }
            return 1;
        }
        else{
            transparency -= 0.5;
            transition.setFillColor(sf::Color(0,0,0, transparency));
            //std::cout << transparency << " ";

            if (transparency <= 0){
                phase = 1;
                return 3;
            }
            return 1;
        }
        return 0;

    }
    void draw_transition(sf::RenderWindow& window){
        window.draw(transition);
    }



    //sky background (blue gradient)
    int windVal = 0;
    sf::Sprite background;
    sf::Texture temp;
    sf::Sprite clouds[5];
    sf::Texture clouds_temp[3];

    sf::Sprite wind;
    bool flipped;
    sf::Texture wind_temp;
    sf::Text windText;
    sf::Font windFont;

    sf::Sprite ground;
    sf::Texture groundTemp;

    sf::RectangleShape transition;
    float transparency;
    int phase;

    
};