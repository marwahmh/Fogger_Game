#include "obstacle.h"

obstacle::obstacle()
{
}

obstacle::obstacle(Texture& texture, int size_x, int size_y)
{
	obsShape.setSize(Vector2f(size_x, size_y));
	obsShape.setTexture(&texture);
}
void obstacle::setSize(int s_x, int s_y)
{
	obsShape.setSize(Vector2f(s_x, s_y));
}

RectangleShape obstacle:: GetShape() 
{
	return obsShape;
}

void obstacle::drawObs(RenderWindow & window)
{
	window.draw(obsShape);
}

void obstacle::moveObs( int stepx)
{
		obsShape.move(stepx, 0);
}

void obstacle::setTexture(Texture& new_texture)
{
	obsShape.setTexture(&new_texture);
}

void obstacle:: setPosition(int x, int y)
{
	obsShape.setPosition(x, y);
}

float obstacle::getPositionX()
{
	return obsShape.getPosition().x;
}
float obstacle::getPositionY()
{
	return obsShape.getPosition().y;
}
obstacle::~obstacle()
{
}
