#include <SFML/Graphics.hpp>
#include<iostream>
#include "include/map.h"
#include <unordered_map>
#include "Boarders.h"
#include "SFMLNode.h"
#include "HelperFunctions.h"
#include <thread>
#include <string>
#include<map>
#include "include/all_paths.h"
unordered_map<string, unordered_map<string, Route>> Map::adjList;
Text pathInfo, allPathsTextInfo;
void drawLine(SFMLNode node1, SFMLNode node2, RenderWindow &window)
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(node1.shape.getPosition().x + 20, node1.shape.getPosition().y + 22);
    lines[1].position = sf::Vector2f(node2.shape.getPosition().x + 20, node2.shape.getPosition().y + 22);
    window.draw(lines);
}
void checkRepulsion(map<string, SFMLNode>& graph)
{
	for (auto& i : graph)
	{
		for (auto& j : graph)
		{
			if (i.first == j.first)
				continue;
			double x1 = i.second.shape.getPosition().x + 20, y1 = i.second.shape.getPosition().y + 22, x2 = j.second.shape.getPosition().x + 20, y2 = j.second.shape.getPosition().y + 22;
			if (helperFunctions::getDistance(x1 + 20, y1 + 22, x2 + 20, y2 + 22) <= 150)
			{
				//cout << "SHOULD BE REPULSING\n";
				double slope = (y2 - y1) / (x2 - x1);
				if (i.second.speedX || i.second.speedY || j.second.speedX || j.second.speedY)
					continue;
				double thetaRad = atan(slope);
				i.second.speedX = 0.4 * cos(thetaRad);
				i.second.speedY = 0.4 * sin(thetaRad);
				j.second.speedX = 0.4 * cos(thetaRad);
				j.second.speedY = 0.4 * sin(thetaRad);
				if (i.second.shape.getPosition().x < j.second.shape.getPosition().x)
					i.second.speedX = -abs(i.second.speedX), j.second.speedX = abs(j.second.speedX);
				else
					i.second.speedX = abs(i.second.speedX), j.second.speedX = -abs(i.second.speedX);

				if (i.second.shape.getPosition().y < j.second.shape.getPosition().y)
					i.second.speedY = abs(i.second.speedY), j.second.speedY = -abs(j.second.speedY);
				else
					i.second.speedY = -abs(i.second.speedY), j.second.speedY = abs(j.second.speedY);
			}
		}
	}
}
map<string, bool> helperFunctions::vis;
int SFMLNode::cnt = 0, pathCnt = 1;
using namespace std;
using namespace sf;
int Map::cnt = 0;
bool SFMLNode::active = false, isAllPaths = false;
map<string, int>Map::hash;
string DATA_PATH = "../Project1/data/data.txt";
map <string, SFMLNode> graph;
queue <int> allPathsCosts;


int main()
{
	Font font;
	font.loadFromFile("PoetsenOneRegular.ttf");
	pathInfo.setFont(font);
	allPathsTextInfo.setFont(font);
	allPathsTextInfo.setPosition(0, 40);
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
	queue <vector <string>> allPathsQ;
	string source = "Cairo", destination = "Dahab";
	Text curText;
	curText.setFont(font);
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
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::B) {
					traverseResult = helperFunctions::bfs("Cairo");
				}
				if (event.key.code == Keyboard::Z) {
					vector<pair<string,string>> v = Map::Dijkstra("Asyut","Dahab").second;
					queue<string> t;
					for (auto i : v)
						t.push(i.first);
					t.push("Dahab");
					traverseResult = t;
				}
				if (event.key.code == Keyboard::D) {
					traverseResult = helperFunctions::dfs("Cairo", traverseResult);
					vis.clear();
				}
				if (event.key.code == Keyboard::Q)
				{
					isAllPaths = true;
					AllPaths allPaths(Map::adjList, source, destination);
					allPaths.computeAllPaths();
					for (auto& i : allPaths.allPathsVector)
					{
						pathInfo.setString("Path # " + to_string(pathCnt));
						allPathsCosts.push(i.first);
						traverseResult.push(source);
						for (auto& j : i.second)
							traverseResult.push(j[1]), allPathsQ.push(j);
					}
				}
			}
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

			if (isAllPaths && x != source)
			{
				auto curv = allPathsQ.front();
				allPathsQ.pop();
				allPathsTextInfo.setString("From  " + curv[0] + "  to  " + curv[1] + " by " + curv[2] + "  with cost:  " + curv[3]);
			}
			else if (isAllPaths)
			{
				pathInfo.setString("Path # " + to_string(pathCnt) + "  with total cost =  " + to_string(allPathsCosts.front()));
				allPathsCosts.pop();
			}
		}
		for (auto& i : graph)
		{
			i.second.checkCollision(graph, window), window.draw(i.second.shape);
			
			curText.setString((string)i.second.cityName.getString());
			curText.setFillColor(Color::Red);
			curText.setScale({ 0.6,0.6 });
			curText.setPosition({ i.second.shape.getPosition().x, i.second.shape.getPosition().y + 10 });
			window.draw(curText);
		}
		SFMLNode node = graph.begin()->second;
		checkRepulsion(graph);
		window.draw(pathInfo);
		window.draw(allPathsTextInfo);
		window.display();
		if (!traverseResult.empty()) {
			this_thread::sleep_for(2.5s);
			graph[x].shape.setFillColor(Color::Green);
			if (traverseResult.front() == destination && isAllPaths)
				pathCnt++, pathInfo.setString("Path # " + to_string(pathCnt)), allPathsTextInfo.setString("");
			if (traverseResult.size() == 1 && isAllPaths)
				pathInfo.setString("");
			if (traverseResult.empty() && isAllPaths)
				isAllPaths = false;
			traverseResult.pop();
		}
    }

    return 0;
}