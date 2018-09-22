#ifndef MOVINGPLATFORMV_H
#define MOVINGPLATFORMV_H

#include "Entity.h"

class MovingPlatformV : public Entity
{
public:
	MovingPlatformV(AnimationManager &a, Level &lev, int x, int y) :Entity(a, x, y)
	{
		option("MovingPlatformV",  0, 0.03, 0, "move");
	}

	void update(float time)
	{		
		y += dy * time;
		timer += time;
		if (timer>6000) { dy *= -1; timer = 0; }
		anim.tick(time);
	}

};

#endif MOVINGPLATFORMV_H

