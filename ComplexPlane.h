#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State {CALCULATING, DISPLAYING};

class ComplexPlane : public Drawable
{
	private:
		VertexArray m_vArray;
		State m_state;
		Vector2f m_mouseLocation;
		Vector2i m_pixel_size;
		Vector2f m_plane_center;
		Vector2f m_plane_size;
		int m_zoomCount;
		float m_aspectRatio;
		
		int countInterations(Vector3f coord);
		void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
		Vector2f mapPixelToCoords(Vector2i mousePixel);
		
	public:
		ComplexPlane(int w, int h);
		void draw(RenderTarget& target, RenderStates states) const;
		void zoomIn();
		void zoomOut();
		void setCenter(Vector2i coord);
		void setMouseLocaton(Vector2i coord);
		void loadText(Text& text);
		void updateRender();
};
