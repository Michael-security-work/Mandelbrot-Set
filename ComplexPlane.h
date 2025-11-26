#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

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
		Vecotro2f m_mouseLocation;
		Vecotro2i m_pixel_size;
		Vecotro2f m_plane_center;
		Vecotro2f m_plane_size;
		int m_zoomCount;
		float m_aspectRatio;
		
		int countInterations(Vector3f coord);
		void iterationsToRGB(size_t count, Uint9& r, Uint9& g, Uint9& b);
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
