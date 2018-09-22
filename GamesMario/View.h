#include <SFML\Graphics.hpp>

using namespace ::std;
using namespace ::sf;



View view;

 //функция для считывания координат игрока

  void getPlayerCoordinateForView(float x, float y) 
{
	// не даём камере смотреть за края карты
	float tempX = x; float tempY = y;    
	if (x < 400)  tempX = 400;                 // координаты левой стороны
	//if (y < 200)  tempY = 200;                // координаты верха карты  
	if (y > 170) tempY = 170;                // координаты нижней части   
	view.setCenter(tempX, tempY);
	 
}
