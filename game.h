#include "components/tower.h"
#include "components/cannon.h"
#include "components/ball.h"
#include "components/PowerBar.h"
#include "components/health.h"
#include "components/sky.h"
#include "components/trees.h"
#include <SFML/Audio.hpp>

class Game{
public:
    Game(sf::VideoMode VM_in, std::string name_in);
    ~Game();

    //returns true if window is still open (game not exited)
    bool isRunning(); 

    //primary game "engine"
    void engine();



        


private:
    sf::RenderWindow *window;
    sf::Event ev;

    sky background;           
    trees tree;
    
    health health_left;
    health health_right;

    PowerBar power_left;
    PowerBar power_right;

    tower tower_left;
    tower tower_right;

    cannon cannon_left;
    cannon cannon_right;

    ball cannonBall;

    //left side turn
    bool left_turn;
    //1 cannon angling/firing, 2 cannonball animation, 4 transition
    int phase;

    sf::Clock gameClock;
    sf::Clock transClock;
    sf::Clock shotClock;

    sf::RectangleShape half;

    bool done;
    bool stop;

    sf::Font font;
    sf::Text gameOver;
    sf::Music background_music;

    sf::Music shot;
    sf::Music explode;


};

