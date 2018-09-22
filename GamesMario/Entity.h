#ifndef Entity_H
#define Entity_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "level.h"

using namespace ::sf;
//using namespace ::std;

/////////////////////////////// общий класс игроков монстров ///////////////////////////
class Entity
{
public:
	
	float dx, dy, x, y, w, h;
	AnimationManager anim;
    std::vector<Object> obj;
	bool life, dir;
	float timer, timer_end;
	std::string Name;
	int Health;

	Entity(AnimationManager &A, int X, int Y)
	{
		anim = A;
		x = X;
		y = Y;
		dir = 0;		
		life = true;
		timer = 0;
		timer_end = 0;
		dx = dy = 0;		
	}

virtual void update(float time) = 0;
	void draw(RenderWindow &Window)
	{
		anim.draw(Window, x, y);
	}
	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}

	void option(std::string NAME, float SpeedX = 0,  float SpeedY = 0, int HEALTH = 10,  std::string FIRST_ANIM = "")
	{
		Name = NAME;
		if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SpeedX;
		dy = SpeedY;
		Health = HEALTH; 
	}
};
#endif Entity_H

