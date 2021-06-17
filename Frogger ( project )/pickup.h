#include<SFML/Graphics.hpp>
using namespace sf;
class pickup
{
private:
	RectangleShape pickupShape;
	bool exist = true;
public:
	pickup();
	pickup(Texture & texture, int size_x, int size_y);
	void setTexture(Texture &texture);
	void setSize(int, int);
	void setPosition(int x, int y);
	void drawPickup(RenderWindow &window);
	void changeTexture(Texture new_texture);
	void movepickup(int stepx);
	float getPositionX();
	float getPositionY();
	void setexist(bool exist);
	bool getexist() const;
	RectangleShape GetShape() const;

	~pickup();
};

