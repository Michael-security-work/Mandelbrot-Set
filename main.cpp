#include <SFML/Graphics.hpp>
#include <iostream>

#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Rainbow Screen", Style::Default);

	while (window.isOpen())
	{
		///Input
		Event event;
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}
		///Update

		///Draw
		window.clear();
		//window.draw(...);
		
		window.display();

	} 
}
