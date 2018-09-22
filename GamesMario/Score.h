#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
//#include "Entity.h"

using namespace ::std;

class Score
{
public:
	
		Font font;//����� 
		font.loadFromFile("images/CyrilicOld.TTF");//�������� ������ ������ ���� ������
		Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		text.setColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
		//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	void update(int k)

		text.setString("�����:");//������ ������ ������
	    text.setPosition(view.getCenter().x, view.getCenter().y);//������ ������� ������, ����� ������

	void draw(RenderWindow &window)
	{
		
		window.draw(text);//����� ���� �����
	}

};
#endif SCORE_H