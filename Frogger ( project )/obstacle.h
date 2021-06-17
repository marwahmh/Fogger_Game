#include <SFML/Graphics.hpp>
using namespace sf;
class obstacle
{
private:

RectangleShape obsShape;

public:

obstacle();
obstacle(Texture & texture, int size_x, int size_y);
void drawObs (RenderWindow &window);
void moveObs (int stepx);
void setTexture(Texture & new_texture);
void setPosition(int x, int y);
void setSize(int s_x, int s_y);
float getPositionX();
float getPositionY();

RectangleShape GetShape() ;

~obstacle();
};
