#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_state = State::CALCULATING;
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = static_cast<float>(pixelHeight) / static_cast<float>(pixelWidth);
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_plane_center = Vector2f(0.f, 0.f);
	m_zoomCount = 0;

	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	
	return Vector2f(0.f, 0.f);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for(int j = 0; j < m_pixel_size.x; j++)
			for(int i = 0; i < m_pixel_size.y; i++)
			{
				Vertex& v = m_vArray[j + i * m_pixel_size.x];
				v.position = {(float)j, (float)i};
			}
	}
	m_state = State::DISPLAYING;
}
void ComplexPlane::zoomIn()
{
	m_zoomCount;
}
void ComplexPlane::zoomOut()
{
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center.x = static_cast<float>(mousePixel.x);
	m_plane_center.y = static_cast<float>(mousePixel.y);
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
}
void ComplexPlane::loadText(Text& text)
{
	stringstream s;
	s << "Mandelbrot Set";
	s << "\nCenter: (" << to_string(m_mouseLocation.x) << ',' << to_string(m_mouseLocation.y) + ')';
	s << "\nCursor: (" << to_string(m_plane_center.x) << ',' << to_string(m_plane_center.y) << ')';
	s << "\nLeft-click to Zoom in";
	s << "\nRight-click to Zoom out";
	text.setString(s.str());
}
size_t ComplexPlane::countIterations(Vector2f coord)
{
	return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	
}