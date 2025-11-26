#include "ComplexPlane.h"

int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width - 100;
	int pixelHeight = VideoMode::getDesktopMode().height - 100;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Rainbow Screen", Style::Default);
	
	 Font font;
	 font.loadFromFile("fonts/DejaVuSansMono.ttf");
	 
	 Text text;
	 text.setFont(font);
	 text.setFillColor(Color::White);

	while (window.isOpen())
	{
		///Input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			
			if(event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					
				}
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}
		///Update

		///Draw
		window.clear();
		//window.draw(...);
		
		window.display();

	} 
}
