#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
//#include "Menu.h"
#include "Animation.h"
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Coins.h"
#include "HealthBar.h"
#include "MovingPlatform.h"
#include "MovingPlatformV.h"
#include "Bullet.h"
#include "Bonus.h"
#include "level.h"
#include "Screen.h"
#include "cScreen.h"
#include "tinyxml\tinyxml.h"

using namespace ::std;
using namespace ::sf;

// ������� � ��������� ���� �� �������� ������ ����
class screen_1 : public cScreen
{
private:
	Texture enemy_t, moveplatform_t, megaman_t, bullet_t, bg, coins, moveplatformV_v, bonus;
	AnimationManager anim, anim2, anim3, anim4, anim5, anim6, anim7;
	Level lvl;

public:
	screen_1(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_1::screen_1(void)
{

	lvl.LoadFromFile("resurs/Level2.tmx");

	bg.loadFromFile("images/bg22.png");
	enemy_t.loadFromFile("images/enemy.png");
	moveplatform_t.loadFromFile("images/movingPlatform.png");
	moveplatformV_v.loadFromFile("images/movingPlatformV.png");
	megaman_t.loadFromFile("images/megaman.png");
	bullet_t.loadFromFile("images/bullet.png");
	coins.loadFromFile("images/coinsSM.png");
	bonus.loadFromFile("images/bonus2.png");

	anim2.create("move", bullet_t, 7, 9, 8, 8, 1, 0, 0);
	anim2.create("explode", bullet_t, 27, 5, 18, 18, 4, 0.01, 29, false);
	anim.loadFromXML("resurs/anim_megaman.xml", megaman_t); /// �������� ������ �� XML
	anim.animList["jump"].loop = 0; //������ ������ �� ����������� �������� ��� ������
	anim.animList["Pdead"].loop = 0; //������ �� ����������� �������� ���� ����� ����
									 //// ����� �������� ������ ��������////

	anim2.create("move", bullet_t, 7, 9, 8, 8, 1, 0, 0);
	anim2.create("explode", bullet_t, 27, 5, 18, 18, 4, 0.01, 29, false);
	anim3.create("move", enemy_t, 0, 0, 18, 16, 2, 0.001, 18);////x, y, w, h, count, speed, step-��� ����
	anim3.create("dead", enemy_t, 58, 0, 16, 16, 1, 0);
	anim4.create("move", moveplatform_t, 0, 0, 95, 22, 1, 0);
	anim5.create("move", moveplatformV_v, 0, 0, 95, 22, 1, 0);
	anim6.create("move", coins, 0, 0, 32, 34, 7, 0.003, 32);
	// �������� ��������.������� (��������, x, y, w, h,  ����������� ������ �������� ��������, ��� �������� h ��� w)
	anim7.create("move", bonus, 0, 0, 16, 32, 5, 0.006, 16);
}

int screen_1::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;

	while (Running)
	{
		View view(FloatRect(0, 0, vidX, vidY));      //������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.

		/////////// ��������� ���������� ����////
		Font font;//����� 
		font.loadFromFile("images/CyrilicOld.TTF");//�������� ������ ������ ���� ������
		/////��������� ������ ���������� ����////
		Text textH("", font, 10);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		textH.setFillColor(sf::Color::Yellow);//��������� ����� � ������. ���� ������ ��� ������, �� �� ��������� �� �����
		//// ��������� ������ ���������� ����������� ������ ��������
		Text textS("", font, 10);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		textS.setFillColor(sf::Color::Yellow);

		/////////////��� ������
		Sprite background(bg);
		background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);

		//////�������� ������� �������� �� XML 
		std::list<Entity*>entities;
		std::list<Entity*>::iterator it;

		std::vector<Object> e = lvl.GetObjects("enemy");
		for (int i = 0; i < e.size(); i++)
			entities.push_back(new ENEMY(anim3, lvl, e[i].rect.left, e[i].rect.top));
		e = lvl.GetObjects("MovingPlatform");
		for (int i = 0; i < e.size(); i++)
			entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top));
		e = lvl.GetObjects("MovingPlatformV");
		for (int i = 0; i < e.size(); i++)
			entities.push_back(new MovingPlatformV(anim5, lvl, e[i].rect.left, e[i].rect.top));
		e = lvl.GetObjects("Coins");
		for (int i = 0; i < e.size(); i++)
			entities.push_back(new COINS(anim6, lvl, e[i].rect.left, e[i].rect.top));
		e = lvl.GetObjects("Bonus");
		for (int i = 0; i < e.size(); i++)
			entities.push_back(new BONUS(anim7, lvl, e[i].rect.left, e[i].rect.top));

		Object pl = lvl.GetObject("player");
		PLAYER Mario(anim, lvl, pl.rect.left, pl.rect.top);
		/// �������� ��� ��������
		HealthBar healthBar;

		Clock clock;            // ������� �������

		while (App.isOpen()) /// ������� ���� ���� ���� ������� 1
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 500; // ���������� �������� ����
			if (time > 40) time = 40;

			/*������������ ����� ��� �������� ���� ����� 2*/
			//Event Event;
			while (App.pollEvent(Event))
			{
				if (Event.type == Event::Closed) /// ���������� ������� ���� ���� �������
				{
					return (-1);
				}

				/////// ����� ��� ������� �������� ���� ����
				if (Event.type == Event::KeyPressed)
					if (Event.key.code == Keyboard::Space)
					{
						entities.push_back(new Bullet(anim2, lvl, Mario.x + 10, Mario.y + 28, Mario.dir));
					}

				if (Event.key.code == Keyboard::Escape)
				{
					return (0); break;
				}
			}

			/////////////////////���� ���������� ������ � �������� � ������/////////////////////
			float offsetX = Mario.x;
			float offsetY = Mario.y;
			////////////// ������������ ��������� ������///////////////
			if (Mario.x < (vidX / 2)) offsetX = ((vidX / 2) + 10); //// ����� �������
			if (Mario.y <= vidY - 200) offsetY = vidY / 2; //// ����
			if (Mario.y > (vidY - (vidY / 2))) offsetY = ((vidY / 2) + 195);  // ���
			//if (Mario.x > 2880) offsetX = 2880; //// ������ �������


			///////////////���������� �������///////////////////////////
			if (Keyboard::isKeyPressed(Keyboard::A)) Mario.key["Left"] = true;
			if (Keyboard::isKeyPressed(Keyboard::D)) Mario.key["Right"] = true;
			if (Keyboard::isKeyPressed(Keyboard::W)) Mario.key["UP"] = true;
			if (Keyboard::isKeyPressed(Keyboard::S)) Mario.key["DOWN"] = true;
			if (Keyboard::isKeyPressed(Keyboard::Space)) Mario.key["Space"] = true;

			//////////���� �������������� � ���������
			for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
			{
				Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
				b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
				if (b->life == false) { it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
				else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
			}

			///////////������ ������������ � ���������
			for (it = entities.begin(); it != entities.end(); it++)
			{
				//1. �����
				if ((*it)->Name == "Enemy")
				{
					Entity *enemy = *it;
					if (enemy->Health <= 0) continue;
					if (Mario.getRect().intersects(enemy->getRect()))
						if (Mario.dy > 0) { enemy->dx = 0; Mario.dy = -0.2; enemy->Health = 0; Mario.ScoreEnemy++; } // ���� ����� ����� ������� ������, �� ������ � ������� ���� � �����
						else if (!Mario.hit)
						{
							Mario.Health -= 10; Mario.hit = true;
							if (Mario.dir) Mario.x += 10; else Mario.x -= 20;
						}

					for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++) //
					{
						Entity *bullet = *it2; //��� ��������, ����� �� ������ (*it)->
						if (bullet->Name == "Bullet")
							if (bullet->getRect().intersects(enemy->getRect())) /// � ���� ���� ����������� � �������� ���� ��
							{
								enemy->dx += 0.1; bullet->dx = 0; bullet->Health = 0; enemy->Health -= 5;  //����� ���� =0, �� ����� ����� ����� ������� 5
								if (enemy->Health <= 0) { Mario.ScoreEnemy++; }    // ���� ����� ����� ����� ������� ���� � �����     
							}

						if (bullet->Name == "Bullet")
							if (bullet->x > Mario.x + 200)
							{
								bullet->life = false;
							}
					}
				}
				//2. ���������� ��������� �������������
				if ((*it)->Name == "MovingPlatform")
				{
					Entity *movPlat = *it;
					if (Mario.getRect().intersects(movPlat->getRect()))
						if (Mario.dy > 0)
							if (Mario.y + Mario.h < movPlat->y + movPlat->h)
							{	///////////// ������ ����� � ����������- movPlat->h- movPlat->h
								Mario.y = movPlat->y - 35;  Mario.x += movPlat->dx*time; Mario.STATE = PLAYER::stay; Mario.dy = movPlat->dy = 0;
							}
				}

				// 3. ���������� ��������� �����������
				if ((*it)->Name == "MovingPlatformV")
				{
					Entity *movPlatV = *it;
					if (Mario.getRect().intersects(movPlatV->getRect()))  //������� ����������� ������ � �������
						if (Mario.dy > 0)    // ���� ����� ������ � > 0
						// � ���� ������ ������� ������ � ��� � ������ ��� �������� ������� � ��� ������
							if (Mario.y + Mario.h < movPlatV->y + movPlatV->h)
							{
								/* �����
								1. �������� ������ �� � = �������� ������� �� � ����� ������ ������� ������
								2. �������� ������ �� � = �������� �������
								3. ��������� �������� ������  */
								Mario.y = movPlatV->y - Mario.h + 3; Mario.x += movPlatV->dx*time; Mario.dy = 0; Mario.STATE = PLAYER::stay;
							}
				}

				// 4. ���� �������
				if ((*it)->Name == "Coins")
				{
					Entity *Coins = *it;
					if (Mario.getRect().intersects(Coins->getRect())) { Mario.PlayScore += Coins->Health; Coins->Health = 0; }
				}

				// 5. �������� �����
				if ((*it)->Name == "Bonus")
				{
					Entity *bonus = *it;
					if (Mario.getRect().intersects(bonus->getRect())) { Mario.BonusSpeed = 2; bonus->Health = 0; }
				}

				//6. �������� ������

			}

			//	/// ���������� ����� //////////////

				/// c ��������� ////////////
				// �������� ����������
			std::ostringstream playerScoreString;
			//������� � ��� ����� �����, �� ���� ��������� ������
			playerScoreString << Mario.PlayScore;
			//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
			textH.setString("�������:" + playerScoreString.str());
			//������ ������� ������, �������� �� ������ ������
			textH.setPosition(offsetX - (vidX / 3), offsetY - (vidY / 2));
			/////////////////////////

			/////////// ������ ��������//////////////
			std::ostringstream plScoreEnemy;
			//������� � ��� ����� �����, �� ���� ��������� ������
			plScoreEnemy << Mario.ScoreEnemy;
			//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
			textS.setString("�������:" + plScoreEnemy.str());
			//������ ������� ������, �������� �� ������ ������
			textS.setPosition(offsetX + (vidX / 3), offsetY - (vidY / 2));
			//////////////////////////////////////////////////////////////

		///������������� ���������� ������ �� ������
			view.setCenter(offsetX, offsetY);
			App.setView(view);

			Mario.update(time);

			//// ��������� ��� ��������
			healthBar.update(Mario.Health);

			///// ������ ���////////
			background.setPosition(view.getCenter());
			App.draw(background);

			//��������� ������ �����
			lvl.Draw(App);

			/// ��������� �������� ����������� enemy � �����
			for (it = entities.begin(); it != entities.end(); it++) { (*it)->draw(App); }
			/// ��������� ������
			Mario.draw(App);
			/// ��������� ��� ��������
			healthBar.draw(App);
			/// ��������� ������
			App.draw(textS);
			App.draw(textH);
			//��������� ������ ����
			App.display();
		}
	}

	//���� ��� ����� �������, �� ��� ����� ������ �� �����
	return -1;
}

#endif GAME_H

