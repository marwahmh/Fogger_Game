
#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
#pragma once
class message
{
	private:
		Text  Msg;
		Font MsgFont;
		
		


public:
	message();
	message(std::string);
	~message();
	void printGameOver(RenderWindow&,int,int);
	void printWin(RenderWindow&,int,int);
	void printExit(RenderWindow&,int,int);
	void printScore(RenderWindow&,int,int,int);
	Text getText() const;

};

