#include "game.h"
#include <math.h>

Game::Game(sf::VideoMode VM_in, std::string name_in) : health_left(true), health_right(false), power_left(true), power_right(false),
tower_left(true), tower_right(false), cannon_left(true), cannon_right(false){
    this->window = new sf::RenderWindow(VM_in, name_in, sf::Style::Titlebar | sf::Style::Close);
    left_turn = true;
    phase = 1;
    background.updateWind();
    tree.updateHeight();
    half.setSize(sf::Vector2f(450, 600));
    half.setFillColor(sf::Color(0,0,0,190));
    done = false;
    stop = false;
    font.loadFromFile("sprite/font.ttf");
    gameOver.setFont(font);
    gameOver.setCharacterSize(50);
    gameOver.setString("GAME  OVER");
    gameOver.setFillColor(sf::Color(150, 50, 50));
    gameOver.setPosition(450 - gameOver.getGlobalBounds().width / 2, 100);
    background_music.openFromFile("music/battle.ogg");
    background_music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0),sf::seconds(70)));
    background_music.setLoop(true);
    background_music.setVolume(50);

    shot.openFromFile("music/cannon.ogg");
    shot.setPlayingOffset(sf::milliseconds(10));
    explode.openFromFile("music/explosion.ogg");
    explode.setPlayingOffset(sf::milliseconds(10));
    shot.setVolume(70);
    explode.setVolume(70);
}

Game::~Game(){
    delete this->window;
}

bool Game::isRunning(){
    return this->window->isOpen();
}


void Game::engine(){
    int frame = 0;
    double addition = 0;

    bool up = false;
    bool down = false;
    bool hit = false;

    int shotPower;
    int power;
    float y_mag;
    float x_mag;
    int test;
    background_music.play();
    while(isRunning()){
        while(this->window->pollEvent(ev)){
            up = false;
            down = false;
            if (ev.type == sf::Event::Closed){
                this->window->close();              
            }
            if (ev.type == sf::Event::KeyPressed){
                if (phase == 1){
                    if (ev.key.code == sf::Keyboard::Up){
                        up = true;
                    }
                    if (ev.key.code == sf::Keyboard::Down){
                        down = true;
                    }
                    if (ev.key.code == sf::Keyboard::Space && phase == 1){
                        phase = 2;
                        shot.stop();
                        shot.play();
                        if (left_turn){
                            shotPower = power_left.getShotPower();
                            power = power_left.getPower();
                            x_mag = (float(cos(cannon_left.getAngle() / 180.0 * M_PI))) * shotPower + background.getWind() / 1.5;
                            //std::cout << x_mag << std::endl << (float(cos(cannon_right.getAngle() / 180.0 * M_PI))) * shotPower << " " << background.getWind() / 1.5 << std::endl;
                            y_mag = float(sin(cannon_left.getAngle() / 180.0 * M_PI)) * shotPower;
                            cannonBall.set_position(35, 425);
                        }
                        else{
                            shotPower = power_right.getShotPower();

                            power = power_right.getPower();   
                            x_mag = -1 * (float(cos(cannon_right.getAngle() / 180.0 * M_PI))) * shotPower + background.getWind() / 1.5;
                            //std::cout << x_mag << std::endl << -1 * (float(cos(cannon_right.getAngle() / 180.0 * M_PI))) * shotPower << " " << background.getWind() / 1.5 << std::endl;
                            y_mag = float(sin(cannon_right.getAngle() / 180.0 * M_PI)) * shotPower;
                            cannonBall.set_position(850, 425);
                        }
                        //std::cout << shotPower << " " << x_mag << " " << y_mag << " " << power;
                    }
                }
            }
            if(left_turn){
                if (up && !down){
                    cannon_left.angle_up(1);
                }
                if (down && !up){
                    cannon_left.angle_down(1);
                }
            }
            else{
                if (up && !down){
                    cannon_right.angle_up(1);
                }
                if (down && !up){
                    cannon_right.angle_down(1);
                }
                
            }
        }
        if (phase == 1){
            if (gameClock.getElapsedTime().asMilliseconds() >= 3){
                
                if(left_turn){
                    power_left.updateScale();
                    power_left.updatePower();
                }
                else{
                    power_right.updateScale();
                    power_right.updatePower();
                }
                background.update();
                gameClock.restart();
            }
            this->window->clear();
            background.draw(*(this->window));
            tower_left.draw(*(this->window));
            tower_right.draw(*(this->window));
            cannon_left.draw(*(this->window));
            cannon_right.draw(*(this->window));
            health_left.draw(*(this->window));
            health_right.draw(*(this->window));
            tree.draw(*(this->window));
            if (left_turn){
                power_left.draw(*(this->window));
            }          
            else{
                power_right.draw(*(this->window));
            }  
        }

        else if (phase == 2){
            if (shotClock.getElapsedTime().asMilliseconds() >= 2){
                if(left_turn){
                    if (!hit){
                        y_mag = cannonBall.update(x_mag, y_mag);
                        if (tower_right.collide(cannonBall.getX(), cannonBall.getY())){      
                            hit = true;
                            explode.stop();
                            explode.play();
                            health_right.setHealth(health_right.getHealth() - power);
                            tower_right.update_tower(health_right.getHealth());
                        }
                    }
                    else{
                        addition += 0.03;
                        frame += addition;
                    }
                }
                else{
                    if (!hit){
                        y_mag = cannonBall.update(x_mag, y_mag);
                        if (tower_left.collide(cannonBall.getX(), cannonBall.getY())){      
                            hit = true;
                            explode.stop();
                            explode.play();
                            health_left.setHealth(health_left.getHealth() - power);
                            tower_left.update_tower(health_left.getHealth());                       
                        }
                    }
                    else{
                        addition += 0.03;
                        frame += addition;
                    }        
                }

                if (cannonBall.getX() > 900 || cannonBall.getX() < -3){
                    phase = 3;
                    test = 1;

                }
                if (cannonBall.getY() > 505){
                    phase = 3;
                    test = 1;

                }
                if (tree.collide(cannonBall.getX(), cannonBall.getY())){
                    phase = 3;
                    test = 1;
                }
                if (frame >= 8000){
                    phase = 3;
                    test = 1;
                }
                shotClock.restart();
            }
            if(gameClock.getElapsedTime().asMilliseconds() >= 3){
                background.update();

                gameClock.restart();
                //std::cout << frame <<" ";

            }
            this->window->clear();
            background.draw(*(this->window));
            tower_left.draw(*(this->window));
            tower_right.draw(*(this->window));
            health_left.draw(*(this->window));
            health_right.draw(*(this->window));
            tree.draw(*(this->window));
            if (left_turn){
                power_left.draw(*(this->window));
            }
            else{
                power_right.draw(*(this->window));
            }
            if (!hit){
                cannonBall.draw(*(this->window));
            }
            cannon_left.draw(*(this->window));
            cannon_right.draw(*(this->window));
            if (hit){
                cannonBall.draw_explosion(*(this->window), frame);
            }
        }
        
        else{ //phase == 3
            if (transClock.getElapsedTime().asMilliseconds() >= 3){
                if (test == 1 || done){
                    background.update();
                }
                if (test == 2){
                    if (health_left.getHealth() <= 0){
                        half.setPosition(sf::Vector2f(0,0));
                        done = true;
                    }
                    if (health_right.getHealth() <= 0){
                        half.setPosition(sf::Vector2f(450, 0));
                        done = true;

                    }
                    left_turn = !left_turn;
                    background.updateWind();
                    tree.updateHeight();
                    cannon_left.reset();
                    cannon_right.reset();
                }
                if (test == 3 && !done){
                    phase = 1;
                    frame = 0;
                    addition = 0;
                    hit = false;
                    power_left.resetPower();
                    power_right.resetPower();
                }
                if (test == 3 && done){
                    stop = true;
                }
                if (!stop){
                    test = background.update_transition();
                }
                //std::cout << test << " ";
                transClock.restart();

            }
            this->window->clear();
            background.draw(*(this->window));
            tower_left.draw(*(this->window));
            tower_right.draw(*(this->window));
            cannon_left.draw(*(this->window));
            cannon_right.draw(*(this->window));
            health_left.draw(*(this->window));
            health_right.draw(*(this->window));
            tree.draw(*(this->window));
            if (left_turn){
                power_left.draw(*(this->window));
            }          
            else{
                power_right.draw(*(this->window));
            } 
            if (done){
                this->window->draw(half);
                this->window->draw(gameOver);
            }
            background.draw_transition(*(this->window));
        }   

        //control cannon, fire cannon, transition to next side
        window->display();
    }

}
