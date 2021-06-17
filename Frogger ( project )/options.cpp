#include "options.h"

options::options(int w, int h)
{
	if (!font.loadFromFile("NewRules.ttf"))
	{
		std::cout << "failed to load menu font";
	}

	optionspictures[0].loadFromFile("soundon.png");
   optionspictures[1].loadFromFile("soundoff1.png");


	option[0].setFont(font);
	option[0].setFillColor(Color::Red);
	option[0].setString("sound On");
	option[0].setPosition(Vector2f(w / 2, h / (Max_items_options + 1) * 1));

	option[1].setFont(font);
	option[1].setFillColor(Color::White);
	option[1].setString("sound off");
	option[1].setPosition(Vector2f(w / 2, h / (Max_items_options + 1) * 2));

	option_pics[0].setTexture(&optionspictures[0]);
	option_pics[1].setTexture(&optionspictures[1]);
	for (int i = 0; i < 2; i++)
	{
		option_pics[i].setSize(Vector2f(50, 50));

		option_pics[i].setPosition(w / 4, h / (Max_items_options + 1) * (i + 1));

	}
	index_selected = 0;
}
void options::createMenu(RenderWindow& window)
{
	for (int i = 0; i < Max_items_options; i++)
		window.draw(option[i]);
	for (int i=0;i<2;i++)
	window.draw(option_pics[i]);
}
void options::MoveUp()
{
	if (index_selected - 1 >= 0)
	{
		option[index_selected].setFillColor(Color::White);
		index_selected--;
		option[index_selected].setFillColor(Color::Red);
	}
}
void options::MoveDown()
{
	if (index_selected + 1 < Max_items_options)
	{
		option[index_selected].setFillColor(Color::White);
		index_selected++;
		option[index_selected].setFillColor(Color::Red);
	}
}
int options::getSelected() const
{
	return index_selected;
}
options::options()
{
}
/*
Event event
while( window.pollEvent(event)
{
switch (event.type)
{
case:: Event:: KeyReleased:
switch(event.key.code)
{
case Keyboard::Up:
menu.MoveUp();
break
case Keyboard::Down:
menu.MoveDown();
break;
case Keyboard::Return:
switch(menu.getSelected())
{
case 0:
std::cout<<" Start Pressed " << std::endl;
break;
case 1:
std::cout<<" options Pressed " << std::endl;
break;
case 2:
std::cout<<" HighScores Pressed " << std::endl;
break;
case 3:
window.close();
break;
}
break;
}

*/