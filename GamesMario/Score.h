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
	
		Font font;//шрифт 
		font.loadFromFile("images/CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
		Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	void update(int k)

		text.setString("Монет:");//задает строку тексту
	    text.setPosition(view.getCenter().x, view.getCenter().y);//задаем позицию текста, центр камеры

	void draw(RenderWindow &window)
	{
		
		window.draw(text);//рисую этот текст
	}

};
#endif SCORE_H