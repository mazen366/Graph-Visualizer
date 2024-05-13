#include <SFML/Graphics.hpp>
#include<iostream>
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
#include<map>
using namespace std;
using namespace sf;
int Map::cnt = 0;
map<string, int>Map::hash;
string DATA_PATH = "../Project1/data/data.txt";
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    DataManager dataManager = DataManager();
    dataManager.readData(DATA_PATH);
    dataManager.printAdjList();
    cout<<Map::Dijkstra("Cairo", "Dahab").first;
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