#include<SFML/Graphics.hpp>
#include<SFML\Audio.hpp>
#include "frog.h" 
#include"obstacle.h"
#include"MainMenu.h"
#include"message.h"
#include<iostream>
#include<fstream>
#include<string>
#include"options.h"
#include"pickup.h"
#include<vector>
using namespace sf;
using namespace std;
vector<int> scores;
Clock clock_msg;
int const rows = 13;
int const cols = 20;
int const rowslog = 10; ////////////////////
int const colslog = 10;////////////////
int const tile_size = 50;
SoundBuffer horn_buffer;
SoundBuffer jump_buffer;
SoundBuffer gameover_buffer;
SoundBuffer water_buffer;
SoundBuffer  Coin_buffer;
SoundBuffer  heart_buffer;
SoundBuffer clock_buffer;

Sound water_sound;
Sound gameOver_sound;
Sound horn;
Sound jump;
Sound coin_sound;
Sound heart_sound;
Sound clock_sound;

Clock coinC;
Clock coinspinC;
Clock heartC;


Clock carC;
Clock timer_clock;
Text timer_text;
Text score;
int timer_int = 60; 
int freeze = 5;
Text Level_Name;
Text lives;
Font font;
RectangleShape flag_win;
bool game_End = false;
bool sound_ON = true;

float duration = float();

#define step 50
#define number_of_cars 1
#define number_of_turtles 1
#define number_of_logs 1
#define number_of_CarRows 3
#define number_of_LogRows 2
#define number_of_turtleRows 2
#define coin_number 4
#define heart_number 3

pickup coins[coin_number];
pickup hearts[heart_number];
pickup clockshape;

obstacle cars[3][number_of_cars];
obstacle turtles[2][number_of_turtles];
obstacle logs[2][number_of_logs];

RectangleShape tunnels[number_of_CarRows], tunnels1[number_of_CarRows], bridges[4], bridges1[4];

MainMenu menu(600, 600);
options options_menu(600, 300);

frog Frog(3, 0);    ////////////////

ifstream background;
Texture land, water, street, tunnel, carR, carB, carO, Turtle, frog_pic, Log, flag_texture, bridge,coin, heart, coin_side1, clock_pic;

Text HighScores_text[6];

bool HighScores_flag = true;

ifstream HighScores_read;
ofstream HighScores_write;
int x1;
RenderWindow window;
RenderWindow Menu_window;
RectangleShape A[rows][cols];
message gameOver("Modia.otf");
message win("September.otf");
message Exit("Modia.otf");
RectangleShape B[rowslog][colslog];
RectangleShape frogShape;       ////////////////
void level_One();
void handle(RenderWindow &window, RenderWindow& Menu_window, frog & Frog, MainMenu&menu);
void Menu();
void sound_off();
void set_coins_positions(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
void set_hearts_positions(int xh0, int yh0, int xh1, int yh1, int xh2, int yh2, int xh3, int yh3);
void modify_situation()
{
	Frog.setfrogposition(550, 705);
	Frog.dec_lives();
	if (Frog.getlives() == 0)
	{
		Frog.setalive(false);
		gameOver_sound.play();
	}
}

void sort(vector<int> & a)
{
	int temp;

	for (int k = 1; k < a.size(); k++)
		for (int c = 0; c < a.size() - k; c++)
			if (a[c] < a[c + 1])
			{
				temp = a[c];
				a[c] = a[c + 1];
				a[c + 1] = temp;

			}

}

void read_from_file()
{
	int t;
	int c = 0; 
	HighScores_read.open("HighScores_file.txt");
	if (HighScores_read.is_open())
	{
	
		while ( c !=5)
		{
			if (!HighScores_read.eof())
			{
				HighScores_read >> t;
				scores.push_back(t);
				c++;
			}
		}
	}
	while (scores.size() < 5)
	{
		scores.push_back(0);
	}

	HighScores_read.close();
}
void process_file()
{
	scores.push_back(Frog.getscore());
	sort(scores);
	scores.erase(scores.end()-1);
}
void write_to_file()
{

	HighScores_write.open("HighScores_file.txt");
	if (HighScores_write.is_open())
		for (int i = 0; i < 5; i++)
		{
			HighScores_write << scores[i] << endl;
		}

	HighScores_write.close();
}


bool check_water(frog&Frog)
{
	bool flag = false;
			
			for (int i = 0; i < number_of_turtleRows; i++)
				for (int j = 0; j < number_of_turtles; j++)
					if (Frog.intersect_obs(turtles[i][j].GetShape()))
					{
						flag = true;
						
					}
			for (int i = 0; i < number_of_LogRows; i++)
				for (int j = 0; j < number_of_logs; j++)
					if (Frog.intersect_obs(logs[i][j].GetShape()))
					{
						
						flag = true;
					}
	
		
			if (Frog.getfrogpositiony() > 150 && Frog.getfrogpositiony() < 350 && !flag)
			{
				if (sound_ON)
				{
					water_sound.play();
				}
				return true;
				
			}
			else
			{
				return false;
			}

}


int main()
{

	read_from_file();

	if (!font.loadFromFile("Modia.otf"))
		cout << "error font not loaded";
	Level_Name.setString("Level 1");
	Level_Name.setFillColor(Color::Red);
	Level_Name.setFont(font);
	Level_Name.setPosition(100, 50);
	lives.setString("Lives " + std::to_string(Frog.getlives()));
	lives.setFillColor(Color::Red);
	lives.setFont(font);
	lives.setPosition(970, 50);
	timer_text.setFont(font);
	timer_text.setPosition(100, 750);
	timer_text.setFillColor(Color::Red);
	timer_text.setString("Time left: " + std::to_string(timer_int));
	score.setFont(font);
	score.setPosition(970, 750);
	score.setFillColor(Color::Red);
	score.setString("Score:" + std::to_string(Frog.getscore()));
	if (!horn_buffer.loadFromFile("horns.wav"))
		cout << "error loading horns.wav";
	if (!jump_buffer.loadFromFile("jump.wav"))
		cout << "error loading jump";
	if (!gameover_buffer.loadFromFile("fuck_you.wav"))
		cout << "error loading game_over.wav";
	if(!water_buffer.loadFromFile("water.wav"))
		cout << "error loading game_over.wav";
	jump_buffer.loadFromFile("jump.wav");
	jump.setBuffer(jump_buffer);
	jump.setVolume(30);
	horn_buffer.loadFromFile("horns1.wav");
	horn.setBuffer(horn_buffer);
	gameover_buffer.loadFromFile("fuck_you.wav");
	gameOver_sound.setBuffer(gameover_buffer);
	horn.setVolume(5);
	water_buffer.loadFromFile("water.wav");
	water_sound.setBuffer(water_buffer);
	Coin_buffer.loadFromFile("Coin.wav");
	coin_sound.setBuffer(Coin_buffer);
	heart_buffer.loadFromFile("heart.wav");
	heart_sound.setBuffer(heart_buffer);
	clock_buffer.loadFromFile("clock.wav");
	clock_sound.setBuffer(clock_buffer);
	for (int i = 0; i < 6; i++)
	{
		HighScores_text[i].setFont(font);
		HighScores_text[i].setFillColor(Color::Yellow);
	}
	HighScores_text[0].setFillColor(Color::Cyan);

	Menu();

}
void handle(RenderWindow &window, RenderWindow& Menu_window, frog & Frog, MainMenu&menu)
{
	Event event;
	while (Menu_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			Menu_window.close();
			break;
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
				menu.MoveUp();
				break;
			case Keyboard::Down:
				menu.MoveDown();
				break;
			case Keyboard::Return:
				switch (menu.getSelected())
				{
				case 0:
				{
					std::cout << " Start Pressed " << std::endl;
					Menu_window.close();
					
					if (sound_ON)
					{
						horn.play();
						horn.setLoop(true);
					}
					level_One();
					
					break;
				}
				case 1:
				{
					RenderWindow Options_window;
					Options_window.create(VideoMode(600, 400), "Options");

					while (Options_window.isOpen())
					{
						Options_window.clear(Color::Black);
						options_menu.createMenu(Options_window);
						Options_window.display();

						Event options_event;
						while (Options_window.pollEvent(options_event))
						{
							switch (options_event.type)
							{
							case::Event::Closed:
								Options_window.close();
								break;
							case Event::KeyReleased:
								switch (options_event.key.code)
								{
								case::Keyboard::Up:
									options_menu.MoveUp();
									break;
								case::Keyboard::Down:
									options_menu.MoveDown();
									break;
								case::Keyboard::Return:
									switch (options_menu.getSelected())
									{
									case 0:
										std::cout << "sound on pressed" << endl;
										sound_ON = true;
										break;
									case 1:
									{
										std::cout << "sound off pressed" << endl;
										sound_ON = false;
										sound_off();
										break;
									}
									}
								}
								break;
							}
						}
					}
					break;

				}
				case 2:
				{
					std::cout << " HighScores Pressed " << std::endl;
					RenderWindow HighScores_window;
					HighScores_window.create(VideoMode(300, 500), "High Scores");
					for (int i = 0; i < 6; i++)
						HighScores_text[i].setPosition(50, 50 * (i + 1));

					HighScores_text[0].setString("High Scores:");
					int k;
					HighScores_read.open("HighScores_file.txt");
						for (int i = 1; i < 6; i++)
						{
							if (HighScores_read.is_open())
							HighScores_read >> k;
							HighScores_text[i].setString(std::to_string(k));
						}

					HighScores_read.close();
					Event event3;

					while (HighScores_window.isOpen())
					{
						HighScores_window.clear(Color::Black);
						for (int i = 0; i < 6; i++)
						HighScores_window.draw(HighScores_text[i]);
						HighScores_window.display();

						while (HighScores_window.pollEvent(event3))
						{
							if (event3.type == Event::Closed)
								HighScores_window.close();
						}

					}						
					
					break;

				}

				case 3:
				{
					RenderWindow exit_window;
					exit_window.create(VideoMode(480, 200), "exit");
					while (exit_window.isOpen())
					{
						Event event_exit;
						exit_window.clear(Color::Black);
						Exit.printExit(exit_window, 10, 50);
						exit_window.display();
						while (exit_window.pollEvent(event_exit))
						{
							switch (event_exit.type)
							{
							case::Event::Closed:
								exit_window.close();
								break;
							case::Event::KeyReleased:
								switch (event_exit.key.code)
								{
								case::Keyboard::Y:
									exit_window.close();
									Menu_window.close();
									break;
								case::Keyboard::N:
									exit_window.close();
									break;
								}
							}

						}
					}
					break;
				}

				break;
				}
				break;
			}
		}
	}
		

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					window.close();
					sound_off();
					break;
				case Event::KeyPressed:

					switch (event.key.code)
					{

					case Keyboard::Down:
					case Keyboard::S:
						if (!game_End)
						{
							Frog.move_down();
							if (sound_ON)
								jump.play();
						}
						break;
					case Keyboard::Up:
					case Keyboard::W:
						if (!game_End)
						{
							Frog.move_up();
							if (sound_ON)
								jump.play();
						}
						break;
					case Keyboard::Right:
					case Keyboard::D:
						if (!game_End)
						{
							Frog.move_right();
							if(sound_ON)
							jump.play();
						}
						break;
					case Keyboard::Left:
					case Keyboard::A:
						if (!game_End)
						{
							Frog.move_left();
							if (sound_ON)
								jump.play();
						}
						break;
					case Keyboard::Space:
						if (sound_ON)
						{
							horn.play();
							horn.setLoop(true);
						}
						level_One();

						break;
					case Keyboard::Escape:
						
						window.close();
						sound_off();
						Menu();
						break;

					}

					
					break;
				}
			}


		
	
}
void level_One()
{
	

	game_End = false;
	timer_int = 60;
	freeze = 5;
	Frog.setscore(0);
	window.create(VideoMode(1200, 850), "Frogger!!");

    for (int i = 0; i < coin_number; i++)
		coins[i].setexist(true);
	for (int i = 0; i < heart_number; i++)
		hearts[i].setexist(true);

	set_coins_positions(175, 215, 230, 315, 280, 410, 700, 510);
	set_hearts_positions(125, 150, 125, 250, 450, 460, 280, 410); //9999999
	clockshape.setPosition(900, 450);



	HighScores_flag = true;

	if (!flag_texture.loadFromFile("flag.png"))
		cout << "error flag.jpg";
	if (!carR.loadFromFile("RedCar.png"))
		cout << "error RedCar.jpg";
	if (!Turtle.loadFromFile("Turttle.png"))
		cout << "error Turtle.jpg";
	if (!carO.loadFromFile("CarOrange.png"))
		cout << "error CarOrange.jpg";
	if (!carB.loadFromFile("BlueCar.png"))
		cout << "error BlueCar.jpg";
	if (!land.loadFromFile("sand2.jpg"))
		cout << "error Sand2.jpg";
	if (!water.loadFromFile("blue1.jpg"))
		cout << "error blue1.jpg";
	if (!street.loadFromFile("street5.jpg"))
		cout << "error street5.jpg";
	if (!tunnel.loadFromFile("tunnel.png"))
		cout << "error tunnel.png";
	if (!frog_pic.loadFromFile("frog.png"))
		cout << "error frog2.png";    
	if (!bridge.loadFromFile("bridge1.png"))
		cout << "error bridge.png";
	if (!Log.loadFromFile("log.png"))
		cout << "error log.png";
	if (!coin.loadFromFile("coin.png"))
		cout << "error coin.png";
	if (!heart.loadFromFile("heart.png"))
		cout << "error heart.png";
	if (!coin_side1.loadFromFile("coin_side1.png"))
		cout << "error coin_side1.png";
	if (!clock_pic.loadFromFile("clock.png"))
		cout << "error clock.png";
	Frog.setfrogtexture(frog_pic);
	Frog.setlives(3);
	Frog.setalive(true);
	Frog.setfrogposition(550, 700);
	Frog.setfrogsize(40, 40);
	flag_win.setSize(Vector2f(50, 50));
	flag_win.setPosition(600, 100);
	flag_win.setTexture(&flag_texture);

	for (int i = 0; i < coin_number; i++)
	{
		coins[i].setTexture(coin);
		coins[i].setSize(25, 25);
	}
	for (int i = 0; i < heart_number; i++)
	{
		hearts[i].setTexture(heart);
		hearts[i].setSize(40, 20);
	}

	clockshape.setTexture(clock_pic);
	clockshape.setSize(50, 50);
	clockshape.setexist(false);

	for (int i = 0; i < number_of_CarRows; i++)
	{
		tunnels[i].setTexture(&tunnel, true);
		tunnels1[i].setTexture(&tunnel, true);

		tunnels[i].setPosition(100, 400 + (i * 50));
		tunnels1[i].setPosition(1050, 400 + (i * 50));

		tunnels[i].setSize(Vector2f(50, 50));
		tunnels1[i].setSize(Vector2f(50, 50));

	}

	for (int i = 0; i < 4; i++)
	{
		bridges[i].setTexture(&bridge, true);
		bridges1[i].setTexture(&bridge, true);

		bridges[i].setPosition(100, 150 + (i * 50));
		bridges1[i].setPosition(1050, 150 + (i * 50));

		bridges[i].setSize(Vector2f(50, 50));
		bridges1[i].setSize(Vector2f(50, 50));

	}



	int x = 150;

	for (int i = 0; i < number_of_CarRows; i++)
	{
		for (int j = 0; j < number_of_cars; j++)
		{
			cars[i][j].setSize(50, 40);
			switch (i)
			{
			case 0:
				cars[i][j].setTexture(carR);
				cars[i][j].setPosition(x + 75, 405);
				break;
			case 1:
				cars[i][j].setTexture(carB);
				cars[i][j].setPosition(x + 200, 455);
				break;
			case 2:
				cars[i][j].setTexture(carO);
				cars[i][j].setPosition(x, 505);
				break;

			}
			x += 150;

		}
		x = 175;
	}

	x = 125;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < number_of_turtles; j++)
		{
			turtles[i][j].setSize(40, 40);
			turtles[i][j].setTexture(Turtle);


			switch (i)
			{
			case 0:
				turtles[i][j].setPosition(x, 150);

				break;
			case 1:
				turtles[i][j].setPosition(x, 250);
				break;
			}
			x += 75 + (20 * j);

		}
		x = 125;

	}


	x = 175;


	for (int i = 0; i < number_of_LogRows; i++)
	{
		for (int j = 0; j < number_of_logs; j++)
		{
			logs[i][j].setSize(70, 20);
			logs[i][j].setTexture(Log);


			switch (i)
			{
			case 0:
			{
				logs[i][j].setPosition(x, 215);
				x += 135;
			}
			break;
			case 1:
			{
				logs[i][j].setPosition(x + 75, 315);
				x += 135;
			}
			break;
			}


		}
		x = 155;


	}
	


	background.open("background.txt");
	if (background.is_open())
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (!background.eof())
					background >> x1;

				A[i][j].setPosition(j*tile_size + 100, i*tile_size + 100);
				A[i][j].setSize(Vector2f(tile_size, tile_size));

				switch (x1)
				{
				case 0:
					A[i][j].setTexture(&land);
					break;
				case 1:
					A[i][j].setTexture(&water);
					break;
				case 2:
					A[i][j].setTexture(&street);
					break;

				}
			}
	}

	background.close();



	while (window.isOpen())
	{

		window.clear();


		
		lives.setString("Lives " + std::to_string(Frog.getlives()));
		timer_text.setString("Time Left: " + std::to_string(timer_int));
		score.setString("Score:" + std::to_string(Frog.getscore()));

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				window.draw(A[i][j]);

		if ((timer_int == 20) || (timer_int == 55))
			clockshape.setexist(true);

		if ((timer_int == 15) || (timer_int == 45))
			clockshape.setexist(false);




		
	

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < number_of_turtles; j++)
				turtles[i][j].drawObs(window);

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < number_of_logs; j++)
				logs[i][j].drawObs(window);

for (int i = 0; i < coin_number; i++)
			coins[i].drawPickup(window);

		for (int i = 0; i < heart_number; i++)
			hearts[i].drawPickup(window);

		clockshape.drawPickup(window);

	for (int i = 0; i < number_of_CarRows; i++)
		{
			for (int j = 0; j < number_of_cars; j++)
			{
				cars[i][j].drawObs(window);

			}
			window.draw(tunnels[i]);
			window.draw(tunnels1[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(bridges[i]);
			window.draw(bridges1[i]);
		}
		if (coinC.getElapsedTime().asMilliseconds() >= 50)
		{
			coins[0].movepickup(5);
			coins[1].movepickup(3);
			
			coinC.restart();
		}
		

		if ((duration > 0.01) && (duration < 0.9))
		{
			coins[0].setTexture(coin);
			coins[1].setTexture(coin_side1);
			coins[2].setTexture(coin);
			coins[3].setTexture(coin_side1);
		}
		if ((duration > 0.9) && (duration < 1.5))
		{
			coins[0].setTexture(coin_side1);
			coins[1].setTexture(coin);
			coins[2].setTexture(coin_side1);
			coins[3].setTexture(coin);
			hearts[0].setSize(50, 30);
			hearts[1].setSize(40, 20);
			hearts[2].setSize(50, 30);
		}
		Time dt = coinspinC.restart();
		duration += dt.asSeconds();
		if (duration > 1.5)
		{
			coins[0].setTexture(coin_side1);
			coins[1].setTexture(coin);
			coins[2].setTexture(coin_side1);
			coins[3].setTexture(coin);
			hearts[0].setSize(40, 20);
			hearts[1].setSize(50, 30);
			hearts[2].setSize(40, 20);
			duration = 0;

		}


		if (heartC.getElapsedTime().asMilliseconds() >= 50)
		{
			hearts[0].movepickup(-2);
			hearts[1].movepickup(-4);
			heartC.restart();

		}
		for (int i = 0; i < 2; i++)
		{
			if (coins[i].getPositionX() > 1025)
				switch (i)
				{
				case 0:
					coins[i].setPosition(125, coins[i].getPositionY());
					break;
				case 1:
					coins[i].setPosition(100, coins[i].getPositionY());
					break;
				}
		}

		for (int i = 0; i < 2; i++)
		{
			if (hearts[i].getPositionX() < 115)
				switch (i)
				{
				case 0:

					hearts[i].setPosition(1015, hearts[i].getPositionY()); 
					break;
				case 1:

					hearts[i].setPosition(1015, hearts[i].getPositionY());
					break;
				}
		}

		for (int i = 0; i < coin_number; i++)
		{
			if ((Frog.intersect_pick(coins[i].GetShape())) && (coins[i].getexist()))
			{
				coin_sound.play();
				Frog.setscore(Frog.getscore() + 10);
			}
			if (Frog.intersect_pick(coins[i].GetShape()))
				coins[i].setexist(false);
		}

		for (int i = 0; i < heart_number; i++)
		{
			if ((Frog.intersect_pick(hearts[i].GetShape())) && (hearts[i].getexist()))
			{
				heart_sound.play();
				Frog.setlives(Frog.getlives() + 1);
			}
			if (Frog.intersect_pick(hearts[i].GetShape()))
				hearts[i].setexist(false);
		}

		if ((Frog.intersect_pick(clockshape.GetShape())) && (clockshape.getexist()))
		{
			clock_sound.play();
			timer_int += 10;
		}
		if (Frog.intersect_pick(clockshape.GetShape()))
			clockshape.setexist(false);


		if (carC.getElapsedTime().asMilliseconds() >= 50)
		{

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < number_of_cars; j++)
				{
					switch (i)
					{
					case 0:
					case 2:
						cars[i][j].moveObs(3);
						break;
					case 1:
						cars[i][j].moveObs(2);
						break;
					}

					if (cars[i][j].getPositionX() >= 1050)
					{
						cars[i][j].setPosition(100, cars[i][j].getPositionY());
					}

					carC.restart();

				}
			for (int i = 0; i < number_of_CarRows; i++)
				for (int j = 0; j < number_of_cars; j++)
				{

					if (Frog.intersect_obs(cars[i][j].GetShape()))
					{
						modify_situation();
					}

				}


			for (int i = 0; i < 2; i++)
				for (int j = 0; j < number_of_turtles; j++)
				{
					switch (i)
					{
					case 0:
					{
						turtles[i][j].moveObs(-2);
						if (Frog.intersect_obs(turtles[i][j].GetShape()))
						{
							Frog.moveFrogTurtle(-2);
							for (int i = 2; i >= 0; i--)
							{
								if (Frog.intersect_obs(bridges[i]) || (Frog.intersect_obs(bridges1[i])))
								{
									modify_situation();
								}
							}
						}
						if (check_water(Frog))
						{
							modify_situation();
						}
						if (turtles[i][j].getPositionX() < 115)
							turtles[i][j].setPosition(1015, turtles[i][j].getPositionY());

					}

					break;

					case 1:
					{
						turtles[i][j].moveObs(-4);
						if (Frog.intersect_obs(turtles[i][j].GetShape()))
						{
							Frog.moveFrogTurtle(-4);
							for (int i = 2; i >= 0; i--)
							{
								if (Frog.intersect_obs(bridges[i]) || (Frog.intersect_obs(bridges1[i])))
								{
									modify_situation();
								}
							}
						}
						if (check_water(Frog))
						{
							modify_situation();
						}
						if (turtles[i][j].getPositionX() < 115)
							turtles[i][j].setPosition(1015, turtles[i][j].getPositionY());

					}
					break;

					}


					



				}

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < number_of_logs; j++)
				{
					switch (i)
					{
					case 0:

						logs[i][j].moveObs(5);
						if (Frog.intersect_obs(logs[i][j].GetShape()))
						{
							Frog.moveFrogLog(5);
							for (int i = 2; i >= 0; i--)
							{
								if (Frog.intersect_obs(bridges[i]) || (Frog.intersect_obs(bridges1[i])))
								{
									modify_situation();
								}
							}
						}
						if (check_water(Frog))
						{
							modify_situation();
						}
						if (logs[i][j].getPositionX() > 1025)
							logs[i][j].setPosition(125, logs[i][j].getPositionY());

						break;

					case 1:

						logs[i][j].moveObs(3);
						if (Frog.intersect_obs(logs[i][j].GetShape()))
						{
							Frog.moveFrogLog(3);
							for (int i = 2; i >= 0; i--)
							{
								if (Frog.intersect_obs(bridges[i]) || (Frog.intersect_obs(bridges1[i])))
								{
									modify_situation();
								}
							}
						}
						if (check_water(Frog))
						{
							modify_situation();
						}
						if (logs[i][j].getPositionX() > 1025)
							logs[i][j].setPosition(100, logs[i][j].getPositionY());

						break;

					}




				}

			}
			
		}
		if (timer_clock.getElapsedTime().asSeconds() >= 1 && !game_End)
		{
			timer_int--;
			timer_clock.restart();
		}
		
		Frog.drawfrog(window);  
		window.draw(Level_Name);
		window.draw(flag_win);
		window.draw(lives);
		window.draw(timer_text);
		window.draw(score);
		if (!Frog.getalive() || timer_int == 0)
		{
			game_End = true;
			gameOver.printGameOver(window, 450, 30);
			if (timer_clock.getElapsedTime().asSeconds() >= 1 && game_End)
			{
				
				freeze--;
				timer_clock.restart();
			}

			
			
		}	
		

		if (Frog.getalive() && Frog.getfrogpositiony() < 150 )
		{

			win.printWin(window, 320, 30);
			if(!game_End)
			Frog.setscore(Frog.getscore()+Frog.getlives()*20+timer_int + 50);
			if (HighScores_flag)
			{
				process_file();
				write_to_file();
				HighScores_flag = false;
			}
			game_End = true;
			if (timer_clock.getElapsedTime().asSeconds() >= 1 && game_End)
			{
             	freeze--;
				timer_clock.restart();
			}

		}

		handle(window, Menu_window, Frog, menu);


		/*if (game_End)
		{
			clock_msg.restart();
			bool sec = false;

			while (game_End && clock_msg.getElapsedTime().asSeconds() <= 5)
				sec = false;
			sec = true;
			if (sec)
			{
				window.close();
				Menu();
			}
		}*/

		/*if (game_End)
		{
			Clock clock_msg;
			if (clock_msg.getElapsedTime().asSeconds() >= 5)
			{
				window.close();
				Menu();
				clock_msg.restart();
			}
		}
		*/
		

		window.display();
		if (freeze == 0)
		{
			sound_off();
			window.close();
			Menu();
			
		}
		HighScores_write.close();

	}
}

void Menu()
{
	Menu_window.create(VideoMode(600, 600), "Menu");



	while (Menu_window.isOpen())
	{
		Menu_window.clear(Color::Black);
		menu.createMenu(Menu_window);
		handle(window, Menu_window, Frog, menu);
		Menu_window.display();
	}
}
void moveObs(int stepx, RectangleShape & obsShape, Clock clock, int ms)
{
	if (clock.getElapsedTime().asMilliseconds() >= ms)
	{
		obsShape.move(stepx, 0);
	}

}
void sound_off()
{
	horn.stop();
}
void movepickup(int stepx, RectangleShape & pickupShape, Clock clock, int ms)
{
	if (clock.getElapsedTime().asMilliseconds() >= ms)
	{
		pickupShape.move(stepx, 0);
	}

}
void set_coins_positions(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
	coins[0].setPosition(x0, y0);
	coins[1].setPosition(x1, y1);
	coins[2].setPosition(x2, y2);
	coins[3].setPosition(x3, y3);
}
void set_hearts_positions(int xh0, int yh0, int xh1, int yh1, int xh2, int yh2, int xh3, int yh3)
{
	hearts[0].setPosition(xh0, yh0);
	hearts[1].setPosition(xh1, yh1);
	hearts[2].setPosition(xh2, yh2);
	hearts[3].setPosition(xh3, yh3);
}
