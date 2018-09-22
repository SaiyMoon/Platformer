#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screen.h"

int main(int argc, char** argv)
{
	//вектором по созданным окнам
	std::vector<cScreen*> Screens;
	int screen = 0;

	//создаём главное окно
	sf::RenderWindow App(sf::VideoMode(vidX, vidY, 32), "HER BAM");

	//курсор мышки невидим
	App.setMouseCursorVisible(false);

	//значения окон
	screen_0 s0;
	Screens.push_back(&s0);
	screen_1 s1;
	Screens.push_back(&s1);

	//если возвращённое от окон значение больше 1 то окно работает
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}