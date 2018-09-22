#ifndef COINS_H
#define COINS_H

#include "Entity.h"

class COINS : public Entity
{
public:
	
	////////анимация монетки//////////
	COINS(AnimationManager &a, Level &lev, int x, int y ) :Entity(a, x, y)
	{
	option("Coins", 0.01, 0, 1, "move");		
	}
		
	void update(float time)
	{///////движение монетки
		/*x += dx * time;
		timer += time;
		if (timer > 1000) { dx *= -1; timer = 0; }*/
		// когда монетку собрали
		if (Health <= 0)
		{
			dy = dx = 0;
			timer_end += time;
			if (timer_end>100) life = false;
		}
		anim.tick(time);
	}	
};
#endif COINS_H
