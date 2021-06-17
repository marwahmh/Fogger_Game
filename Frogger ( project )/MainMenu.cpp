#include "MainMenu.h"



MainMenu::MainMenu(int w , int h)
{
	if (!font.loadFromFile("NewRules.ttf"))
	{
		std::cout << "failed to load menu font";
	}

	if (!start_texture.loadFromFile("start1.png"))
		std::cout << "error start image";
	if (!options_texture.loadFromFile("options.png"))
		std::cout << "error options image";
	if (!HighScores_texture.loadFromFile("HighScores.png"))
		std::cout << "error highscores image";
	if (!exit_texture.loadFromFile("exit.png"))
		std::cout << "error exit image";
	if (!title_texture.loadFromFile("title.png"))
		std::cout << "error exit image";

	title.setTexture(&title_texture);
	title.setPosition(100,0);
	title.setSize(Vector2f(400, 110));


	start_sprite.setTexture(&start_texture);
	start_sprite.setPosition(w / 4,( h / (Max_items + 1) * 1)-2);
	start_sprite.setSize(Vector2f(70, 70));

	options_sprite.setTexture(&options_texture);
	options_sprite.setPosition(w / 4,( h / (Max_items + 1) * 2)-2);
	options_sprite.setSize(Vector2f(70, 70));

	HighScores_sprite.setTexture(&HighScores_texture);
	HighScores_sprite.setPosition(w / 4, (h / (Max_items + 1) * 3)-2);
	HighScores_sprite.setSize(Vector2f(70, 70));

	exit_sprite.setTexture(&exit_texture);
	exit_sprite.setPosition(w / 4,( h / (Max_items + 1) * 4)-2);
	exit_sprite.setSize(Vector2f(70, 70));


	option[0].setFont(font);
	option[0].setFillColor(Color::Red);
	option[0].setString("Start");
	option[0].setPosition(Vector2f(w / 2, h / (Max_items + 1) * 1+10));

	option[1].setFont(font);
	option[1].setFillColor(Color:: White);
	option[1].setString("Options");
	option[1].setPosition(Vector2f(w / 2, h / (Max_items + 1) * 2+10));

	option[2].setFont(font);
	option[2].setFillColor(Color:: White);
	option[2].setString("HighScores");
	option[2].setPosition(Vector2f(w / 2, h / (Max_items + 1) * 3+10));

	option[3].setFont(font);
	option[3].setFillColor(Color:: White);
	option[3].setString("Exit");
	option[3].setPosition(Vector2f(w / 2, h / (Max_items + 1) * 4+10));

	index_selected = 0;


}
void MainMenu::createMenu(RenderWindow& window)
{
	for (int i = 0; i < Max_items; i++)
		window.draw(option[i]);
	window.draw(start_sprite);
	window.draw(exit_sprite);
	window.draw(HighScores_sprite);
	window.draw(options_sprite);
	window.draw(title);
}
void MainMenu::MoveUp()
{
	if (index_selected - 1 >= 0)
	{
		option[index_selected].setFillColor(Color::White);
		option[index_selected].setCharacterSize(30);

		index_selected--;
		option[index_selected].setFillColor(Color::Red);
		option[index_selected].setCharacterSize(50);

	}
}
void MainMenu::MoveDown()
{
	if (index_selected + 1 < Max_items )
	{
		option[index_selected].setFillColor(Color:: White);
		option[index_selected].setCharacterSize(30);

		index_selected++;
		option[index_selected].setFillColor(Color::Red);
		option[index_selected].setCharacterSize(50);

	}
}
int MainMenu::getSelected() const
{
	return index_selected;
}
MainMenu::~MainMenu()
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