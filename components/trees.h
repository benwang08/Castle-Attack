#include <SFML/Graphics.hpp>

struct trees{

    trees(){
        temp.loadFromFile("sprite/bark.jpg");
        tree.setTexture(&temp, false);

        top_temp.loadFromFile("sprite/treetop.png");
        treeTop.setTexture(top_temp);
        treeTop.setScale(0.1, 0.1);

        tree.setSize(sf::Vector2f(25, 100));

        tree.setPosition(437, 410);


    }

    void updateHeight(){
        height = rand() % 200;
        height += 100;
        tree.setSize(sf::Vector2f(30, height));
        tree.setPosition(437, 510 - height);

        treeTop.setPosition(410, 490 - height);
    }

    void draw(sf::RenderWindow &window){
        window.draw(tree);
        window.draw(treeTop);
    }

    bool collide(float x, float y){

        if (x > 435 && x < 460 && y > (510 - height)){
            return true;
        }
        return false;

    }


    int height;
    sf::RectangleShape tree;
    sf::Texture temp;

    sf::Sprite treeTop;
    sf::Texture top_temp;
};