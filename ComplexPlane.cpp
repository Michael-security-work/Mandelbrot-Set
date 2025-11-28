#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_state = State::CALCULATING;
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = static_cast<float>(pixelWidth) / static_cast<float>(pixelHeight);
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_plane_center = Vector2f(0.f, 0.f);
	m_zoomCount = 0;

	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(m_pixel_size.x * m_pixel_size.y);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{

	}
	m_state = State::DISPLAYING;
}
void ComplexPlane::zoomIn()
{

}
void ComplexPlane::zoomOut()
{
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
}
void ComplexPlane::loadText(Text& text)
{
}
size_t ComplexPlane::countIterations(Vector2f coord)
{
	return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	return Vector2f(0.f, 0.f);
}