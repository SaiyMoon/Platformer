#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet:public Entity
{
public:
	
	Bullet(AnimationManager &a, Level &lev, int x, int y, bool dir) :Entity(a, x, y)
	{
		option("Bullet", 0.2, 0, 5, "move");
		if (dir) dx = -0.3;
		obj = lev.GetAllObjects(); 		
	};
		
void update(float time)
	{			
	x += dx*time;	

	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			///////// ��������
			if (obj[i].name == "solid") { dx = dy = 0; Health = 0;}
			
		}
	
	/////// �������� ���������� ����� ���� � ����� �������
	if (x <= 0) Health = 0;
	if (y <= 0) Health = 0;		

		// ���� ����� ���� 0 �� �������� 
	// ����� ���� ��� ����� �������� ��������� ���������, 
	// ��������� ���� �������������� � ��������� �������� � ��������� 
	// ������� ����. �������� ����������� ���� ��������� ����� �����
	// � ����������� ���� ���������� ��� ��������������� �����
	// ������ ��� 350 ��� ����� ����������� �� ����� ���� ������� ������ ���� ��������.
	//���� ��������� ����� ���� �� ���� ���������
		if (Health <= 0)
		{	
			anim.set("explode"); 
			timer_end += time;
			if (timer_end > 350) 
			{
				life = false; anim.isPlaying() == false; timer = 0; dx = dy = 0;			  
			}
			
		}
			
	anim.tick(time);	
	}
///////// ������������ � ��������� //////////////////////

	

};
#endif BULLET_H
