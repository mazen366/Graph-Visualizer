#include "SFMLNode.h"
#include "helperFunctions.h"

SFMLNode::SFMLNode()
{
	cityName.setFont(cityfont);
	cityName.setString("");
	cityName.setFillColor(Color::Red);
	cityName.setScale({ 0.5,0.5 });
	kk = SFMLNode::cnt;
	SFMLNode::cnt++;
	shape = CircleShape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(50 / 2, 50 / 2);
}
SFMLNode::SFMLNode(string name) {
	cityName.setFont(cityfont);
	cityName.setString(name);
	cityName.setFillColor(Color::Red);
	cityName.setScale({ 0.6,0.6 });
	kk = SFMLNode::cnt;
	SFMLNode::cnt++;
	shape = CircleShape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(50 / 2, 50 / 2);
}
void SFMLNode::checkCollision(map <string, SFMLNode>& graph, RenderWindow &window)
{
	auto mouse_pos = sf::Mouse::getPosition(window);
	auto translated_pos = window.mapPixelToCoords(mouse_pos);
	if ((!active || isDragged) && shape.getGlobalBounds().contains(translated_pos) && Mouse::isButtonPressed(Mouse::Left))
	{
		shape.setFillColor(Color::Magenta);
		shape.setPosition(Vector2f(Mouse::getPosition().x - 30, Mouse::getPosition().y - 40));
		active = true;
		isDragged = true;
	}
	else if (active && isDragged)
		active = false, isDragged = false, shape.setFillColor(Color::Green);


	for (auto& i : Map::adjList[this->cityName.getString()]) {
		if (graph[i.first].isDragged)
			continue;

		double distance = helperFunctions::getDistance(shape.getPosition().x, shape.getPosition().y,
			graph[i.first].shape.getPosition().x, graph[i.first].shape.getPosition().y);

		if (distance > 400) // Consider nodes within a certain range
		{
			// Calculate tension force
			double forceMagnitude = (distance - 400) * 0.0001; // Adjust this coefficient as needed
			double thetaRad = atan2(shape.getPosition().y - graph[i.first].shape.getPosition().y,
				shape.getPosition().x - graph[i.first].shape.getPosition().x);
			/*        double thetaRad = atan2(graph[i].shape.getPosition().y - shape.getPosition().y,
						graph[i].shape.getPosition().x - shape.getPosition().x);*/
						// Apply tension force to adjacent node's speed
			graph[i.first].speedX += forceMagnitude * cos(thetaRad);
			graph[i.first].speedY += forceMagnitude * sin(thetaRad);
		}
		//else if (distance < 300) // Consider nodes within a certain range
		//{
		//    // Calculate tension force
		//    double forceMagnitude = (300 - distance) * 0.0008; // Adjust this coefficient as needed
		//    double thetaRad = atan2(graph[i].shape.getPosition().y - shape.getPosition().y,
		//        graph[i].shape.getPosition().x - shape.getPosition().x);

		//    // Apply tension force to adjacent node's speed
		//    graph[i].speedX += forceMagnitude * cos(thetaRad);
		//    graph[i].speedY += forceMagnitude * sin(thetaRad);
		//}
	}
}
void SFMLNode::sinWave(float amplitude, float frequency, float time)
{
	float x = shape.getPosition().x;
	float y = shape.getPosition().y;
	y += amplitude * std::sin(frequency * time);
	shape.setPosition(x, y);
}
void SFMLNode::boarderCollision(Boarders boarders) {
	if (shape.getGlobalBounds().intersects(boarders.upper.getGlobalBounds())) {
		speedY = max(speedY, 0.0);
	}
	if (shape.getGlobalBounds().intersects(boarders.lower.getGlobalBounds())) {
		speedY = min(speedY, 0.0);
	}
	if (shape.getGlobalBounds().intersects(boarders.left.getGlobalBounds())) {
		speedX = max(speedX, 0.0);
	}
	if (shape.getGlobalBounds().intersects(boarders.right.getGlobalBounds())) {
		speedX = min(speedX, 0.0);
	}
	//cout << kk << " " << speedX << " " << speedY << endl;
}
void SFMLNode::showCityNames(RenderWindow & window) {

	cityName.setPosition({ shape.getPosition().x
		,shape.getPosition().y + 10 });
	window.draw(cityName);
}