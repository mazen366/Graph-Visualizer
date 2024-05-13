#include <SFML/Graphics.hpp>
#include<iostream>
#include "include/map.h"
#include <unordered_map>
#include<map>
using namespace std;
using namespace sf;

unordered_map<string, unordered_map<string, Route>> Map::adjList;
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
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}