#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class ENEMY : public Entity
{
public:
	bool onGround; // ���������� ��� ����������� �� ������� ������ ��� �����
	bool r; // ����� ����������� ��� ������������ �� ������
	int c; // ������� ��� ��������� ����������� ��� ������������ �� ������

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
				///////// ��������
				if (obj[i].name == "solid")
				{
					if (dy > 0 && nume == 1) { y = obj[i].rect.top - h; dy = 0; onGround = true; } //���� ����� ������ 
					if (dx > 0 && nume == 0) { x = obj[i].rect.left - w; r = false; }//����������� � �����
					if (dx < 0 && nume == 0) { x = obj[i].rect.left + obj[i].rect.width; r = true; } // ����������� ����
				}
			}		
	}
	void update(float time)
	{
		if (onGround == true) { dy = dy + 0.0015 * time; }
		if (r == true) dx = 0.01; else dx = -0.01;

		anim.tick(time);
		/////�������� �����		
		x += dx * time;
		CollisionE(0);

		y += dy * time;
		CollisionE(1);

		
		////���� ���� ����
		if (Health <= 0)
		{
			anim.set("dead"); dx = dy = 0; life = false;
			timer_end += time; if (timer_end > 4000);
		}		 
	}		
};
#endif ENEMY_H
