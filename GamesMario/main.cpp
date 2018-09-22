#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screen.h"

int main(int argc, char** argv)
{
	//�������� �� ��������� �����
	std::vector<cScreen*> Screens;
	int screen = 0;

	//������ ������� ����
	sf::RenderWindow App(sf::VideoMode(vidX, vidY, 32), "HER BAM");

	//������ ����� �������
	App.setMouseCursorVisible(false);

	//�������� ����
	screen_0 s0;
	Screens.push_back(&s0);
	screen_1 s1;
	Screens.push_back(&s1);

	//���� ������������ �� ���� �������� ������ 1 �� ���� ��������
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}