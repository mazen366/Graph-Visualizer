#include <SFML/Graphics.hpp>
#include<iostream>
#include "include/map.h"
#include <unordered_map>
#include "Boarders.h"
#include "SFMLNode.h"
#include <thread>
#include <string>
#include<map>
unordered_map<string, unordered_map<string, Route>> Map::adjList;
void drawLine(SFMLNode node1, SFMLNode node2, RenderWindow &window)
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(node1.shape.getPosition().x + 20, node1.shape.getPosition().y + 22);
    lines[1].position = sf::Vector2f(node2.shape.getPosition().x + 20, node2.shape.getPosition().y + 22);

    window.draw(lines);
}
int SFMLNode::cnt = 0;
using namespace std;
using namespace sf;
int Map::cnt = 0;
bool SFMLNode::active = false;
map<string, int>Map::hash;
string DATA_PATH = "../Project1/data/data.txt";
map <string, SFMLNode> graph;
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
	queue<string>traverseResult;
	Clock clock;
	map<string, bool>vis;
	Text t;
	
	for (auto& i : Map::adjList)
	{
		
		graph[i.first] = SFMLNode(i.first);
		t.setFont(graph[i.first].cityfont);
		graph[i.first].shape.setPosition(100 + graph[i.first].kk * 200, 100 + graph[i.first].kk * 50);
		graph[i.first].shape.setFillColor(Color::Green);
		//(i % 2 == 0) ? graph[i].shape.setFillColor(Color::Green) : graph[i].shape.setFillColor(Color::Blue), graph[i].shape.setScale(0.8, 0.8);
	}
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
		for (auto& i : graph)
		{
			i.second.boarderCollision(boarders);
			i.second.shape.move(i.second.speedX, i.second.speedY);
			if (i.second.speedX >= 0) {
				i.second.speedX = max(0.0, i.second.speedX - 0.04);
			}
			else
				i.second.speedX = min(0.0, i.second.speedX + 0.04);

			if (i.second.speedY >= 0) {
				i.second.speedY = max(0.0, i.second.speedY - 0.04);
			}
			else
				i.second.speedY = min(0.0, i.second.speedY + 0.04);
		}
		for (auto& i : graph) {
			i.second.sinWave(helperFunctions::randomFloat(0.01, 0.038), helperFunctions::randomFloat(0.8, 0.97), clock.getElapsedTime().asSeconds());
		}
		window.clear();
		boarders.drawBoarders(window);
		for (auto& i : Map::adjList) {
			vis[i.first] = true;
			for (auto j : i.second) {
				if (!vis[j.first])
					drawLine(graph[i.first], graph[j.first], window);
			}
		}
		vis.clear();
		string x = "\0";
		if (!traverseResult.empty()) {
			x = traverseResult.front();
			graph[x].shape.setFillColor(Color::Yellow);
		}
		for (auto& i : graph)
		{
			i.second.checkCollision(graph, window), window.draw(i.second.shape);
			Text curText;
			curText.setFont(i.second.cityfont);
			curText.setString((string)i.second.cityName.getString());
			curText.setFillColor(Color::Red);
			curText.setScale({ 0.6,0.6 });
			curText.setPosition({ i.second.shape.getPosition().x, i.second.shape.getPosition().y + 10 });
			window.draw(curText);
		}
		SFMLNode node = graph.begin()->second;
		window.display();
		if (!traverseResult.empty()) {
			this_thread::sleep_for(1.5s);
			graph[x].shape.setFillColor(Color::Green);
			traverseResult.pop();
		}
    }

    return 0;
}