#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
using namespace sf;
#define Max_items 4
class MainMenu
{
private:
	        int index_selected;
			Texture optionspictures[4], start_texture, options_texture, HighScores_texture, exit_texture, title_texture; 
			Text option[Max_items];
			Font font;
			RectangleShape start_sprite, options_sprite, HighScores_sprite, exit_sprite, title;
public:
	MainMenu(int,int);
	void createMenu(RenderWindow&window);
	void MoveUp();
	void MoveDown();
	int getSelected() const;
	//void handleEvents(RenderWindow& window);
	~MainMenu();
};

