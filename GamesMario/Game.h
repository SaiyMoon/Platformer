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

// создаем и наследуем окно от главного класса окна
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
	anim.loadFromXML("resurs/anim_megaman.xml", megaman_t); /// анимация игрока их XML
	anim.animList["jump"].loop = 0; //ставим запрет на цикличность анимации при прыжке
	anim.animList["Pdead"].loop = 0; //запрет на цикличность анимации если игрок умер
									 //// далее анимации других объектов////

	anim2.create("move", bullet_t, 7, 9, 8, 8, 1, 0, 0);
	anim2.create("explode", bullet_t, 27, 5, 18, 18, 4, 0.01, 29, false);
	anim3.create("move", enemy_t, 0, 0, 18, 16, 2, 0.001, 18);////x, y, w, h, count, speed, step-шаг аним
	anim3.create("dead", enemy_t, 58, 0, 16, 16, 1, 0);
	anim4.create("move", moveplatform_t, 0, 0, 95, 22, 1, 0);
	anim5.create("move", moveplatformV_v, 0, 0, 95, 22, 1, 0);
	anim6.create("move", coins, 0, 0, 32, 34, 7, 0.003, 32);
	// название анимации.создать (текстура, x, y, w, h,  колличество кадров скорость анимации, шаг анимации h или w)
	anim7.create("move", bonus, 0, 0, 16, 32, 5, 0.006, 16);
}

int screen_1::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;

	while (Running)
	{
		View view(FloatRect(0, 0, vidX, vidY));      //размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.

		/////////// текстовая информация очки////
		Font font;//шрифт 
		font.loadFromFile("images/CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
		/////параметры текста выводящего очки////
		Text textH("", font, 10);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		textH.setFillColor(sf::Color::Yellow);//покрасили текст в чёрный. если убрать эту строку, то по умолчанию он белый
		//// параметры текста выводящего колличество убитых монстров
		Text textS("", font, 10);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		textS.setFillColor(sf::Color::Yellow);

		/////////////фон уровня
		Sprite background(bg);
		background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);

		//////загрузка позиций объектов из XML 
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
		/// загрузка бар здоровья
		HealthBar healthBar;

		Clock clock;            // функция времени

		while (App.isOpen()) /// главный цикл пока окно открыто 1
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 500; // регулируем скорость игры
			if (time > 40) time = 40;

			/*обязательная фигня для создания окна часть 2*/
			//Event Event;
			while (App.pollEvent(Event))
			{
				if (Event.type == Event::Closed) /// обработчик событий если окно закрыто
				{
					return (-1);
				}

				/////// чтобы при нажатии вылетала одна пуля
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

			/////////////////////берём координаты игрока и передаем в камеру/////////////////////
			float offsetX = Mario.x;
			float offsetY = Mario.y;
			////////////// ограничиваем видимость камеры///////////////
			if (Mario.x < (vidX / 2)) offsetX = ((vidX / 2) + 10); //// левая граница
			if (Mario.y <= vidY - 200) offsetY = vidY / 2; //// верх
			if (Mario.y > (vidY - (vidY / 2))) offsetY = ((vidY / 2) + 195);  // низ
			//if (Mario.x > 2880) offsetX = 2880; //// правая граница


			///////////////управление игроком///////////////////////////
			if (Keyboard::isKeyPressed(Keyboard::A)) Mario.key["Left"] = true;
			if (Keyboard::isKeyPressed(Keyboard::D)) Mario.key["Right"] = true;
			if (Keyboard::isKeyPressed(Keyboard::W)) Mario.key["UP"] = true;
			if (Keyboard::isKeyPressed(Keyboard::S)) Mario.key["DOWN"] = true;
			if (Keyboard::isKeyPressed(Keyboard::Space)) Mario.key["Space"] = true;

			//////////цикл взаимодействия с объектами
			for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
			{
				Entity *b = *it;//для удобства, чтобы не писать (*it)->
				b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
				if (b->life == false) { it = entities.erase(it); delete b; }// если этот объект мертв, то удаляем его
				else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
			}

			///////////логика столкновения с объектами
			for (it = entities.begin(); it != entities.end(); it++)
			{
				//1. враги
				if ((*it)->Name == "Enemy")
				{
					Entity *enemy = *it;
					if (enemy->Health <= 0) continue;
					if (Mario.getRect().intersects(enemy->getRect()))
						if (Mario.dy > 0) { enemy->dx = 0; Mario.dy = -0.2; enemy->Health = 0; Mario.ScoreEnemy++; } // если врага убили прыжком сверху, то отскок и плюсуем очко к счёту
						else if (!Mario.hit)
						{
							Mario.Health -= 10; Mario.hit = true;
							if (Mario.dir) Mario.x += 10; else Mario.x -= 20;
						}

					for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++) //
					{
						Entity *bullet = *it2; //для удобства, чтобы не писать (*it)->
						if (bullet->Name == "Bullet")
							if (bullet->getRect().intersects(enemy->getRect())) /// и если пуля пересеклась с объектом враг то
							{
								enemy->dx += 0.1; bullet->dx = 0; bullet->Health = 0; enemy->Health -= 5;  //жизнь пули =0, из очков жизни врага вычесть 5
								if (enemy->Health <= 0) { Mario.ScoreEnemy++; }    // если врага убили пулей плюсуем очко к счёту     
							}

						if (bullet->Name == "Bullet")
							if (bullet->x > Mario.x + 200)
							{
								bullet->life = false;
							}
					}
				}
				//2. движущиеся платформы горизонтально
				if ((*it)->Name == "MovingPlatform")
				{
					Entity *movPlat = *it;
					if (Mario.getRect().intersects(movPlat->getRect()))
						if (Mario.dy > 0)
							if (Mario.y + Mario.h < movPlat->y + movPlat->h)
							{	///////////// правим косяк с платформой- movPlat->h- movPlat->h
								Mario.y = movPlat->y - 35;  Mario.x += movPlat->dx*time; Mario.STATE = PLAYER::stay; Mario.dy = movPlat->dy = 0;
							}
				}

				// 3. движущиеся платформы вертикально
				if ((*it)->Name == "MovingPlatformV")
				{
					Entity *movPlatV = *it;
					if (Mario.getRect().intersects(movPlatV->getRect()))  //поверка пересечения игрока и объекта
						if (Mario.dy > 0)    // если игрок падает у > 0
						// и если высота спрайта игрока и его у меньше чем скорость объекта и его высота
							if (Mario.y + Mario.h < movPlatV->y + movPlatV->h)
							{
								/* тогда
								1. скорость игрока по у = скорости объекта по у минус высота спрайта игрока
								2. скорость игрока по х = скорости объекта
								3. состояние анимации стоять  */
								Mario.y = movPlatV->y - Mario.h + 3; Mario.x += movPlatV->dx*time; Mario.dy = 0; Mario.STATE = PLAYER::stay;
							}
				}

				// 4. сбор монеток
				if ((*it)->Name == "Coins")
				{
					Entity *Coins = *it;
					if (Mario.getRect().intersects(Coins->getRect())) { Mario.PlayScore += Coins->Health; Coins->Health = 0; }
				}

				// 5. морковка бонус
				if ((*it)->Name == "Bonus")
				{
					Entity *bonus = *it;
					if (Mario.getRect().intersects(bonus->getRect())) { Mario.BonusSpeed = 2; bonus->Health = 0; }
				}

				//6. пуляющий монстр

			}

			//	/// показываем текст //////////////

				/// c монетками ////////////
				// объявили переменную
			std::ostringstream playerScoreString;
			//занесли в нее число очков, то есть формируем строку
			playerScoreString << Mario.PlayScore;
			//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			textH.setString("Монетки:" + playerScoreString.str());
			//задаем позицию текста, отступая от центра камеры
			textH.setPosition(offsetX - (vidX / 3), offsetY - (vidY / 2));
			/////////////////////////

			/////////// убитых монстров//////////////
			std::ostringstream plScoreEnemy;
			//занесли в нее число очков, то есть формируем строку
			plScoreEnemy << Mario.ScoreEnemy;
			//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			textS.setString("Монстры:" + plScoreEnemy.str());
			//задаем позицию текста, отступая от центра камеры
			textS.setPosition(offsetX + (vidX / 3), offsetY - (vidY / 2));
			//////////////////////////////////////////////////////////////

		///устанавливаем координаты камеры по центру
			view.setCenter(offsetX, offsetY);
			App.setView(view);

			Mario.update(time);

			//// обновляем бар здоровья
			healthBar.update(Mario.Health);

			///// задний фон////////
			background.setPosition(view.getCenter());
			App.draw(background);

			//отрисовка уровня карты
			lvl.Draw(App);

			/// отрисовка объектов наследников enemy с карты
			for (it = entities.begin(); it != entities.end(); it++) { (*it)->draw(App); }
			/// отрисовка игрока
			Mario.draw(App);
			/// отрисовка бар здоровья
			healthBar.draw(App);
			/// отрисовка текста
			App.draw(textS);
			App.draw(textH);
			//отрисовка самого окна
			App.display();
		}
	}

	//если все пошло хреново, то тут точно выйдем из цикла
	return -1;
}

#endif GAME_H

