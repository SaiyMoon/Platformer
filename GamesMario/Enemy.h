#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class ENEMY : public Entity
{
public:
	bool onGround; // переменная для определения на твердом монстр или летит
	bool r; // смена направления при столкновении со стеной
	int c; // костыль для изменения направления при столкновении со стеной

	ENEMY(AnimationManager &a, Level &lev, int x, int y) :Entity(a, x, y)
	{
		option("Enemy", 0, 0.1, 20, "move");
	    obj = lev.GetAllObjects();
		onGround = false; c = 1; r = true;
	}
	void CollisionE(int nume)
  	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				///////// твердыми
				if (obj[i].name == "solid")
				{
					if (dy > 0 && nume == 1) { y = obj[i].rect.top - h; dy = 0; onGround = true; } //если игрок падает 
					if (dx > 0 && nume == 0) { x = obj[i].rect.left - w; r = false; }//стокновение в право
					if (dx < 0 && nume == 0) { x = obj[i].rect.left + obj[i].rect.width; r = true; } // стокновение лево
				}
			}		
	}
	void update(float time)
	{
		if (onGround == true) { dy = dy + 0.0015 * time; }
		if (r == true) dx = 0.01; else dx = -0.01;

		anim.tick(time);
		/////движение врага		
		x += dx * time;
		CollisionE(0);

		y += dy * time;
		CollisionE(1);

		
		////если враг умер
		if (Health <= 0)
		{
			anim.set("dead"); dx = dy = 0; life = false;
			timer_end += time; if (timer_end > 4000);
		}		 
	}		
};
#endif ENEMY_H
