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
	text.setCharacterSize(pixelHeight / 35);
	
	ComplexPlane plane(pixelWidth, pixelHeight);

	while (window.isOpen())
	{
		///Input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			
			if(event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					plane.zoomIn();
					plane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.x));
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					plane.zoomOut();
				}
			}
			if (event.type == Event::MouseMoved)
			{
				plane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.x));
			}
		}
		///Update
		plane.updateRender();
		plane.loadText(text);

		///Draw
		window.clear();
		
		window.draw(plane);
		window.draw(text);
		
		window.display();
	} 
}
