#include <SFML\Graphics.hpp>

using namespace ::std;
using namespace ::sf;



View view;

 //������� ��� ���������� ��������� ������

  void getPlayerCoordinateForView(float x, float y) 
{
	// �� ��� ������ �������� �� ���� �����
	float tempX = x; float tempY = y;    
	if (x < 400)  tempX = 400;                 // ���������� ����� �������
	//if (y < 200)  tempY = 200;                // ���������� ����� �����  
	if (y > 170) tempY = 170;                // ���������� ������ �����   
	view.setCenter(tempX, tempY);
	 
}
