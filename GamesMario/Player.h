#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PLAYER : public Entity
{
public:
	enum { stay, walk, duck, jump, climb, swim, Pdead} STATE;
	bool onLadder, shoot, hit;
	int PlayScore, ScoreEnemy, BonusSpeed;
	std::map<std::string, bool> key;

	PLAYER(AnimationManager &a, Level &lev, int x, int y) :Entity(a, x, y)		
	{
		option("Player", 0, 0, 100, "stay");
		STATE = stay; hit = false; 
		obj = lev.GetAllObjects();
		PlayScore = 0;
		ScoreEnemy = 0;
		BonusSpeed = 1;		

	}
	///////////// ������� ���������� �������///////////
	void Keyboard()
	{ 
		if (life == true)  //// ���� ����� ��� �� ����� ���������
			////// ������ ����������
		{///////// ���� ������ �� ������ "��������� � ����"
			if (key["Left"])
			{
				dir = 1;
				if (STATE != duck) dx = -0.1; /// � �������� �� � ��������� "�����" �� ���� � ����
				if (STATE == stay) STATE = walk; /// ��������� �������� "������" ������ �� "����"
			}
			/// � ��� �����/////
			if (key["Right"])
			{
				dir = 0;
				if (STATE != duck) dx = 0.1;
				if (STATE == stay) STATE = walk;
			}
			//// ���� ������ ������ "� ����"
			if (key["UP"])
			{
				if (onLadder) STATE = climb; 
                /// �� ��������� ������ ��� ���� ��������� � ��������� ������
				if (STATE == stay || STATE == walk) { dy = -0.27; STATE = jump; anim.play("jump"); } 
				if (STATE == climb) dy = -0.05;
				if (STATE == climb) if (key["Left"] || key["Right"]) STATE = stay;
			}

			if (key["DOWN"])
			{
				if (STATE == stay || STATE == walk) { STATE = duck; dx = 0; }
				if (STATE == climb) dy = 0.05;
			}
			
			//// ��� ������� �� ������ ��������� �������� ������� 
			if ((key["Space"]) || life > 0) {shoot = true;}

			/////////////////////���� ������� ��������///////////////////////////
			if (!(key["Right"] || key["Left"]))
			{
				dx = 0;
				if (STATE == walk) STATE = stay;
			}

			if (!(key["UP"] || key["DOWN"]))
			{if (STATE == climb) dy = 0;}

			if (!key["DOWN"])
			{if (STATE == duck) { STATE = stay; }}
			
			if (!key["Space"])
				{shoot = false;}
			///// ��������� ��������� ���� ������//////////
			key["Right"] = key["Left"] = key["UP"] = key["DOWN"] = key["Space"] = false;
		}
	}

	///////////������������ �������� � ��������� ������
	void Animation(float time)
	{  		
		if (STATE == stay) anim.set("stay");
		if (STATE == walk) anim.set("walk");
		if (STATE == jump) anim.set("jump");
		if (STATE == duck) anim.set("duck");
		if (STATE == climb) { anim.set("climb"); anim.pause(); if (dy != 0) anim.play(); }
		if (STATE == Pdead) { anim.set("Pdead");}
		//// ������������� �������� �� ��������////
		
		if (shoot)
		{
			anim.set("shoot");
			timer += time;
			if (timer > 10) { shoot = false; timer = 0; }
		}
		
			if (STATE == walk) anim.set("shootAndWalk"); // ���� � �������� 
		//	if (STATE == duck) anim.set("shootAndDuck"); // ������ � ��������
		
		/// ��������� ���� � ������ ������
		if (hit) 
		{   
			anim.set("hit"); /// �������� �������� ������
			timer += time;
			if (timer>500) { hit = false; timer = 0; } // ����� �������			
		}

		if (dir) anim.flip(); //// ��������� ��� ���� ��������� �������� 

		anim.tick(time);  /// ��������� ����� ��� ��������
	}

	////////������� ����� ����� ��������////
    void draw(RenderWindow &window)
		{anim.draw(window, x, y+h);}
	///////////////////////////////////////
///////// ������� ���������� ��������� //////////
	void update(float time)	
	{
		Keyboard();
		Animation(time);
		
		if (STATE == climb) if (!onLadder) STATE = stay;
		if (STATE != climb) dy += 0.0005*time;
		onLadder = false;

		x += dx*time*BonusSpeed;
		Collision(0);

		y += dy*time;
		Collision(1);

		if (Health <= 0) 
		{
			STATE = Pdead;
			dx = dy = 0;
			life = false; 
		}
	}

	/////////������ ������������ ������ � ���������
	void Collision(int num)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				///////// ��������
				if (obj[i].name == "solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h; dy = 0; STATE = stay;} //���� ����� ������ 
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height; dy = 0;  }   //����� ���� �������� �������  
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }//����������� � ����
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; } // ����������� �����
				}				

				/// ���� ���
				if (obj[i].name == "Hooli")	{Health = 0;}

				///// �� ��������
				if (obj[i].name == "ladder") { onLadder = true; if (STATE == climb) x = obj[i].rect.left - 10; }
				
				//////������ �� ����
				if (obj[i].name == "SlopeLeft")
				{
					FloatRect r = obj[i].rect;
					int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
					if (y>y0)
						if (x + w / 2>r.left) {y = y0; dy = 0; STATE = stay;}
				}
				
				/////������ �� �����
				if (obj[i].name == "SlopeRight")
				{
					FloatRect r = obj[i].rect;
					int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
					if (y > y0)
						if (x + w / 2<r.left + r.width)	{y = y0; dy = 0; STATE = stay;}
				}				
			}
	}
};
#endif PLAYER_H
