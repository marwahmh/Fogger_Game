#include "pickup.h"

pickup::pickup()
{
}
pickup::pickup(Texture& texture, int size_x, int size_y)
{
	pickupShape.setSize(Vector2f(size_x, size_y));
	pickupShape.setTexture(&texture);
}
void pickup::setTexture(Texture & texture)
{
	pickupShape.setTexture(&texture, true);
}
void pickup::setSize(int x, int y)
{
	pickupShape.setSize(Vector2f(x, y));

}
void pickup::setPosition(int x, int y)
{
	pickupShape.setPosition(x, y);
}

RectangleShape pickup::GetShape() const
{
	return pickupShape;
}

void pickup::drawPickup(RenderWindow& window)
{
	if(exist)
	window.draw(pickupShape);
}

void pickup::changeTexture(Texture new_texture)
{
	pickupShape.setTexture(&new_texture, true);
}
void pickup::movepickup(int stepx)
{
	pickupShape.move(stepx, 0);
}
void pickup::setexist(bool exist)
{
	this->exist = exist;
}
bool pickup::getexist() const
{
	return exist;
}
float pickup::getPositionX()
{
	return pickupShape.getPosition().x;
}
float pickup::getPositionY()
{
	return pickupShape.getPosition().y;
}
pickup::~pickup()
{
}
