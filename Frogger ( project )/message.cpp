#include "message.h"
#include<string>
#include<iostream>
using namespace std;
message::message()
{

}
message::message(std::string font)
{
	if (MsgFont.loadFromFile(font))
	{
		Msg.setFont(MsgFont);
		Msg.setFillColor(Color::White);
		Msg.setCharacterSize(30);
		Msg.setStyle(Text::Bold);
	}
}
void message::printGameOver(RenderWindow& window, int x, int y)
{
	Msg.setString("FUCK YOU ASSHOLE !!");
	Msg.setCharacterSize(50);
	Msg.setFillColor(Color::Red);
	Msg.setPosition(x, y);
	window.draw(Msg);
}
Text message::getText() const
{
	return Msg;
}
void message::printWin(RenderWindow& window, int x, int y)
{
	Msg.setString("Congratulations Froogy ! You Won !!");
	Msg.setCharacterSize(40);
	Msg.setFillColor(Color::Red);
	Msg.setPosition(x, y);
	window.draw(Msg);
}
void message::printExit(RenderWindow& window, int x, int y)
{
	Text command;
	command.setFont(MsgFont);
	command.setPosition(x + 5, y + 40);
	command.setFillColor(Color::Red);
	command.setCharacterSize(20);
	Msg.setCharacterSize(20);
	command.setString("press'Y' for yes and 'N' for no");
	Msg.setString("Are You Sure that You Want to Exit?");
	Msg.setPosition(x, y);
	Msg.setStyle(Text::Regular);
	Msg.setFillColor(Color::Red);
	window.draw(Msg);
	window.draw(command);
}
void message::printScore(RenderWindow& window, int x, int y, int score)
{
	Msg.setString("Score" + std::to_string(score));
	Msg.setPosition(x, y);
	window.draw(Msg);
}


message::~message()
{
}
