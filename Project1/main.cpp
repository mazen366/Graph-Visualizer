#include <SFML/Graphics.hpp>
#include "include/map.h"
#include <unordered_map>
#include "Boarders.h"
#include "SFMLNode.h"
unordered_map<string, unordered_map<string, Route>> Map::adjList;
void drawLine(SFMLNode node1, SFMLNode node2, RenderWindow &window)
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(node1.shape.getPosition().x + 20, node1.shape.getPosition().y + 22);
    lines[1].position = sf::Vector2f(node2.shape.getPosition().x + 20, node2.shape.getPosition().y + 22);

    window.draw(lines);
}
int SFMLNode::cnt = 0;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    string dataPath = "data/data.txt";
    Boarders boarders;
    DataManager datamanager;
    datamanager.readData(dataPath);
    datamanager.printAdjList();
    Clock clock;
    SFMLNode test;
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