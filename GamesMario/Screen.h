#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "cScreen.h"

using namespace ::sf;
 
// ������ ������ (����)
int vidX = 1280;
int vidY = 800;

// ����� ���� ��������� �� ���������� ������ ����
class screen_0 : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
	float posX = 280;
	float posY = 220;

public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_0::screen_0(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int screen_0::Run(sf::RenderWindow &App)
{
	View viewMenu(FloatRect(0, 0, vidX, vidY));

	sf::Event Event;
	bool Running = true;
	sf::Texture Texture, aboutTexture;
	sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text Menu1;
	sf::Text Menu2;
	sf::Text Menu3;
	sf::Text Menu4;
	sf::Text Menu5;
	int menuNum = 0;
	int menu = 0;
	sf::Sprite about(aboutTexture);

	if (!Texture.loadFromFile("images/bg2.png"))
	{
		std::cerr << "Error loading bg2.png" << std::endl;
		return (-1);
	}
	Sprite.setTexture(Texture);
	//Sprite.setColor(sf::Color(255, 255, 255 ));//alpha
	if (!Font.loadFromFile("images/CyrilicOld.TTF"))
	{
		std::cerr << "Error loading CyrilicOld.TTF" << std::endl;
		return (-1);
	}
	if (!aboutTexture.loadFromFile("images/about.png"))
	{
	std::cerr << "Error loading about.png" << std::endl;
	return (-1);
	}
	
	// ���� ��������� ������ ����� ���, ������ ������, �����, ������� � ����

	Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Play");
	Menu1.setPosition({ posX, posY - 160 });

	Menu2.setFont(Font);
	Menu2.setCharacterSize(20);
	Menu2.setString("Continue");
	Menu2.setPosition({ posX, posY - 60 });

	Menu3.setFont(Font);
	Menu3.setCharacterSize(20);
	Menu3.setString("Settings");
	Menu3.setPosition({ posX, posY - 100 });

	Menu4.setFont(Font);
	Menu4.setCharacterSize(20);
	Menu4.setString("Exit");
	Menu4.setPosition({ posX, posY });

	Menu5.setFont(Font);
	Menu5.setCharacterSize(20);
	Menu5.setString("About");
	Menu5.setPosition({ posX, posY + 50 });

	/*if (playing)
{
	alpha = alpha_max;
}*/
// ������� ���� ���� �������� ��...
	while (Running)
	{

		while (App.isOpen()) /// ������� ���� ���� ���� ������� 1
		{
		// ����������� �������
			while (App.pollEvent(Event))
			{
				App.setMouseCursorVisible(true);
				// ���� ���� �������
				if (Event.type == sf::Event::Closed)
				{
					App.close(); return (-1); // ���������� ������������ ����� � ���� ���� while 
				}

				///// ���� ������� �� ������ ������ ������ ����, ������, ���������� ���� �������////////
				if (IntRect(posX, posY - 160, 100, 50).contains(Mouse::getPosition()))
				{
					Menu1.setFillColor(sf::Color(255, 0, 0, 255)); menuNum = 1;
				}
				else
				{
					Menu1.setFillColor(sf::Color(255, 255, 255, 255));
				}
				if (IntRect(posX, posY - 60, 100, 50).contains(Mouse::getPosition()))
				{
					Menu2.setFillColor(sf::Color(255, 0, 0, 255)); menuNum = 2;
				}
				else
				{
					Menu2.setFillColor(sf::Color(255, 255, 255, 255));
				}
				if (IntRect(posX, posY - 100, 100, 50).contains(Mouse::getPosition()))
				{
					Menu3.setFillColor(sf::Color(255, 0, 0, 255)); menuNum = 3;
				}
				else
				{
					Menu3.setFillColor(sf::Color(255, 255, 255, 255));
				}
				if (IntRect(posX, posY, 100, 50).contains(Mouse::getPosition()))
				{
					Menu4.setFillColor(sf::Color(255, 0, 0, 255)); menuNum = 4;
				}
				else
				{
					Menu4.setFillColor(sf::Color(255, 255, 255, 255));
				}
				if (IntRect(posX, posY + 50, 100, 50).contains(Mouse::getPosition()))
				{
					Menu5.setFillColor(sf::Color(255, 0, 0, 255)); menuNum = 5;
				}
				else
				{
					Menu5.setFillColor(sf::Color(255, 255, 255, 255));
				}

				////////////���������� ������� �� ������///////
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (menuNum == 1) return (1);   //���� ������ ������ ������, �� ������� �� ���� �������� ������ playing = true;
					if (menuNum == 2)
					if (menuNum == 3)
					if (menuNum == 4) { return (-1); }  // ����� exit App.close();
					if (menuNum == 5) { App.draw(about); App.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); } // ���� � ���������
				}
			}

			//			 //����������� ������� ������
	//			if (Event.type == sf::Event::KeyPressed)
	//			{
	//				switch (Event.key.code)
	//				{
	//				case sf::Keyboard::Up:
	//					menu = 0;
	//					break;
	//				case sf::Keyboard::Down:
	//					menu = 1;
	//					break;
	//				case sf::Keyboard::Return:
	//					if (menu == 0)
	//					{
	//						 ���� ����������� ������ ������ ���������� ����
	//						playing = true;
	//						return (1);
	//					}
	//					else
	//					{
	//						 ����� ��������� ���
	//						return (-1);
	//					}
	//					break;
	//				default:break;
	//				}
	//			}

			////������ ���� �������� ���� ��� �� ������
	//if (alpha<alpha_max)
	//{
	//	alpha++;
	//}
	//Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
	//if (menu == 0)
	//{
	//	Menu1.setFillColor(sf::Color(255, 0, 0, 255));
	//	Menu2.setFillColor(sf::Color(255, 255, 255, 255));
	//	Menu3.setFillColor(sf::Color(255, 0, 0, 255));
	//	Menu4.setFillColor(sf::Color(255, 255, 255, 255));
	//}
	//else
	//{
	//	Menu1.setFillColor(sf::Color(255, 255, 255, 255));
	//	Menu2.setFillColor(sf::Color(255, 0, 0, 255));
	//	Menu3.setFillColor(sf::Color(255, 255, 255, 255));
	//	Menu4.setFillColor(sf::Color(255, 0, 0, 255));
	//}

		
		//������������� ���� �� ������, ��� �� ���� ������������
			App.setView(viewMenu);
			// ������� ������
			App.clear();
			//��������� ������� ����
			App.draw(Sprite);

			//// ���� �� ������ ������� ����
	//if (alpha == alpha_max)
	//{
	//	if (playing)
	//	{
	//		App.draw(Menu3);
	//	}
	//	else
	//	{
	//		App.draw(Menu1);
	//	}
	//	App.draw(Menu2);
	//	App.draw(Menu4);
	//}

			App.draw(Menu1);	
			App.draw(Menu2);
			App.draw(Menu3);
			App.draw(Menu4);			
			App.draw(Menu5);	
			App.display();		
		}
	}	
	
	//���� �� � ����� ����� ��� ������ ����� ��������
	return (-1);
}

#endif SCREEN_H