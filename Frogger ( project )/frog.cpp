#include "frog.h"                     
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

frog::frog()
{

}
frog::frog(int l, int s)
{
	lives = l;
	score = s;
}
void frog::inc_score()
{
	score++;
}

void frog::dec_lives()
{
	lives = lives - 1;
}
void frog::inc_lives()
{
	lives++;
}

frog::~frog()
{
}
void frog::setfrogtexture(Texture&frog_pic)
{
	if (alive)
		frogShape.setTexture(&frog_pic);

}
void frog::setfrogsize(int frogsizex, int frogsizey)
{
	if (alive)
		frogShape.setSize(Vector2f(frogsizex, frogsizey));

}
void frog::setfrogposition(int frogx, int frogy)
{
	if (alive)
		frogShape.setPosition(frogx, frogy);

}
int frog::getfrogpositionx() const
{
	return frogShape.getPosition().x;
}
int frog::getfrogpositiony() const
{
	return frogShape.getPosition().y;
}

void frog::drawfrog(RenderWindow & window)
{
	if (alive)
		window.draw(frogShape);
}
void frog::move_up()
{

	if (alive && frogShape.getPosition().y > 100)
	{
		if (!(frogShape.getPosition().x == 100 && frogShape.getPosition().y == 550) && !(frogShape.getPosition().x == 1050 && frogShape.getPosition().y == 550) && !(frogShape.getPosition().x == 100 && frogShape.getPosition().y == 350) && !(frogShape.getPosition().x == 1050 && frogShape.getPosition().y == 350))
			frogShape.move(0, -step);
	}
}
void frog::move_down()
{

	if (alive && frogShape.getPosition().y < 700)
	{
		if (!(frogShape.getPosition().x == 100 && frogShape.getPosition().y == 350) && !(frogShape.getPosition().x == 1050 && frogShape.getPosition().y == 350))

			frogShape.move(0, step);
	}
}
void frog::move_right()
{

	if (alive && frogShape.getPosition().x <= 1000)
	{
		frogShape.move(step, 0);
	}
}
void frog::move_left()
{
	if (alive && (frogShape.getPosition().x >= 150))
	{
		if (((frogShape.getPosition().y >= 400) && (frogShape.getPosition().y < 550)) || ((frogShape.getPosition().y >= 150) && (frogShape.getPosition().y < 350)))
		{
			if (frogShape.getPosition().x >= 200)
				//	if ((frogShape.getPosition().y < 400) ||( frogShape.getPosition().y >= 550))
				//if(!(frogShape.getPosition().y >= 400) && (frogShape.getPosition().y < 550) && (frogShape.getPosition().x < 200))
				frogShape.move(-step, 0);
		}
		else
			frogShape.move(-step, 0);
	}

}


void frog::setalive(bool alive)
{
	this->alive = alive;
}
bool frog::getalive() const
{
	return alive;
}
void frog::setlives(int l)
{
	lives = l;
}
int frog::getlives() const
{
	return lives;
}
void frog::setscore(int s)
{
	score = s;
}
int frog::getscore()const
{
	return score;
}
bool frog::intersect_obs(RectangleShape obsShape)
{
	if (frogShape.getGlobalBounds().intersects(obsShape.getGlobalBounds()))
		return true;
	else
		return false;
}
bool frog::intersect_pick(RectangleShape pickupShape)
{
	if (frogShape.getGlobalBounds().intersects(pickupShape.getGlobalBounds()))
		return true;
	else
		return false;
}
void frog::moveFrogTurtle(int step)
{
	if (alive && frogShape.getPosition().x > 150)
	{
		frogShape.move(step, 0);
	}

}
void frog::moveFrogLog(int step)
{
	if (alive && frogShape.getPosition().x < 1000)
	{
		frogShape.move(step, 0);
	}

}


