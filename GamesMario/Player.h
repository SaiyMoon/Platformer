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
	///////////// функции управления игроком///////////
	void Keyboard()
	{ 
		if (life == true)  //// если игрок жив то можно управлять
			////// логика управления
		{///////// если нажали на кнопку "стрелочка в лево"
			if (key["Left"])
			{
				dir = 1;
				if (STATE != duck) dx = -0.1; /// и персонаж не в состоянии "сидит" то идем в лево
				if (STATE == stay) STATE = walk; /// состояние анимации "стоять" меняем на "идти"
			}
			/// и так далее/////
			if (key["Right"])
			{
				dir = 0;
				if (STATE != duck) dx = 0.1;
				if (STATE == stay) STATE = walk;
			}
			//// если нажата кнопка "в верх"
			if (key["UP"])
			{
				if (onLadder) STATE = climb; 
                /// из состояния стоять или идти переходим в состояние прыжок
				if (STATE == stay || STATE == walk) { dy = -0.27; STATE = jump; anim.play("jump"); } 
				if (STATE == climb) dy = -0.05;
				if (STATE == climb) if (key["Left"] || key["Right"]) STATE = stay;
			}

			if (key["DOWN"])
			{
				if (STATE == stay || STATE == walk) { STATE = duck; dx = 0; }
				if (STATE == climb) dy = 0.05;
			}
			
			//// при нажатии на пробел состояние стрелять активно 
			if ((key["Space"]) || life > 0) {shoot = true;}

			/////////////////////если клавиша отпущена///////////////////////////
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
			///// обновляем состояние всех кнопок//////////
			key["Right"] = key["Left"] = key["UP"] = key["DOWN"] = key["Space"] = false;
		}
	}

	///////////приравниваем анимацию к состоянию игрока
	void Animation(float time)
	{  		
		if (STATE == stay) anim.set("stay");
		if (STATE == walk) anim.set("walk");
		if (STATE == jump) anim.set("jump");
		if (STATE == duck) anim.set("duck");
		if (STATE == climb) { anim.set("climb"); anim.pause(); if (dy != 0) anim.play(); }
		if (STATE == Pdead) { anim.set("Pdead");}
		//// устанавливаем анимацию ля стрельбы////
		
		if (shoot)
		{
			anim.set("shoot");
			timer += time;
			if (timer > 10) { shoot = false; timer = 0; }
		}
		
			if (STATE == walk) anim.set("shootAndWalk"); // идти и стрелять 
		//	if (STATE == duck) anim.set("shootAndDuck"); // сидеть и стрелять
		
		/// состояние если в игрока ранили
		if (hit) 
		{   
			anim.set("hit"); /// анимация раненого игрока
			timer += time;
			if (timer>500) { hit = false; timer = 0; } // время мигания			
		}

		if (dir) anim.flip(); //// повторяем все если повёрнутая анимация 

		anim.tick(time);  /// обновляем время для анимации
	}

	////////костыль чтобы игрок приседал////
    void draw(RenderWindow &window)
		{anim.draw(window, x, y+h);}
	///////////////////////////////////////
///////// функция обновления состояний //////////
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

	/////////логика столкновения игрока с объектами
	void Collision(int num)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				///////// твердыми
				if (obj[i].name == "solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h; dy = 0; STATE = stay;} //если игрок падает 
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height; dy = 0;  }   //игрок ниже твердого объекта  
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }//стокновение в лево
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; } // стокновение право
				}				

				/// шипы яма
				if (obj[i].name == "Hooli")	{Health = 0;}

				///// на лестнице
				if (obj[i].name == "ladder") { onLadder = true; if (STATE == climb) x = obj[i].rect.left - 10; }
				
				//////подъем на лево
				if (obj[i].name == "SlopeLeft")
				{
					FloatRect r = obj[i].rect;
					int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
					if (y>y0)
						if (x + w / 2>r.left) {y = y0; dy = 0; STATE = stay;}
				}
				
				/////подьем на право
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
