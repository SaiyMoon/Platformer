#ifndef BONUS_H
#define BONUS_H

#include "Entity.h"

class BONUS : public Entity
{
public:

	BONUS(AnimationManager &a, Level &lev, int x, int y) :Entity(a, x, y)
	{
		option("Bonus", 0.01, 0, 1, "move");		
	}

	void update(float time)
	{
		/////движение бонуса
		x += dx * time;
		timer += time;
		if (timer > 2000) { dx *= -1; timer = 0; }
		//// когда монетку собрали
		if (Health <= 0)
		{
			dy = dx = 0;
			timer_end += time;
			if (timer_end>100) life = false;
		}
		anim.tick(time);
	}
};
#endif BONUS_H

