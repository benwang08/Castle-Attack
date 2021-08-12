#include "game.cpp"
#include <iostream>

//tower shooter game
//Benjamin Wang, 2021
int main(){

    //initialize game window
    Game game(sf::VideoMode(900, 600), "Tower Destroyer");
    game.engine();



    return 0;

}