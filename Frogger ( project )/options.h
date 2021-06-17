#include<SFML\Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
#define Max_items_options 2
class options
{
private:
	int index_selected;
	Texture optionspictures[2];
	Text option[Max_items_options];
	RectangleShape option_pics[2];
	Font font;

public:
	options(int, int);
	void createMenu(RenderWindow&window);
	void MoveUp();
	void MoveDown();
	int getSelected() const;
	//void handleEvents(RenderWindow& window);
	options();
};