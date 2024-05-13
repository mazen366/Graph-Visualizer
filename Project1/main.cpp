#include <SFML/Graphics.hpp>
#include "include/map.h"
#include "NodeSfml.h"
#include <unordered_map>
unordered_map<string, unordered_map<string, Route>> Map::adjList;
int main()
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    
    Boarders boarders;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        boarders.drawBoarders(window);
        window.display();
    }

    return 0;
}