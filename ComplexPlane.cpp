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
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::loadText(Text& text)
{
	stringstream s;
	s << "Mandelbrot Set";
	s << "\nCenter: (" << to_string(m_plane_center.x) << ',' << to_string(m_plane_center.y) << ')';
	s << "\nCursor: (" << to_string(m_mouseLocation.x) << ',' << to_string(m_mouseLocation.y) << ')';
	s << "\nLeft-click to Zoom in";
	s << "\nRight-click to Zoom out";
	text.setString(s.str());
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i pixel)
{
	float r = m_plane_center.x + (pixel.x - m_pixel_size.x / 2.0f) * (m_plane_size.x / m_pixel_size.x);
	float i = m_plane_center.y + (pixel.y - m_pixel_size.y / 2.0f) * (m_plane_size.y / m_pixel_size.y);
	return Vector2f(r, i);
}
void ComplexPlane::setCenter(Vector2i pixel)
{
	m_plane_center = mapPixelToCoords(pixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
	m_mouseLocation = mapPixelToCoords(mousPixel);
}
size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z = c;
	int i = 0;
	while (abs(z) < 2.0 && i < MAX_ITER)
	{
		z = z * z + c;
		i++;
	}
	return i;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count > 63) { r = 0; g = 0; b = 0; }
	else
	{
		float ratio = (float)count / 64.0f;
		r = static_cast<Uint8>(100.0f + 255.0f * ratio);
		g = static_cast<Uint8>(50.0f + 1000.0f / ratio);
		b = static_cast<Uint8>(55.0f + 100.0f * ratio);
	}
}
void ComplexPlane::updateRow(int row)
{
	if (row < 0 || row > m_pixel_size.y) return;
	for (int j = 0; j < m_pixel_size.x; j++)
	{
		Vertex& v = m_vArray[j + row * m_pixel_size.x];
		v.position = Vector2f((float)j, (float)row);
		Vector2f coord = mapPixelToCoords(Vector2i(j, row));
		size_t count = countIterations(coord);
		Uint8 r, g, b;
		iterationsToRGB(count, r, g, b);
		v.color = { r, g, b };
	}
}
static void startThread(ComplexPlane* plane, int startRow, int endRow)
{
	for (int i = startRow; i < endRow; i++) plane->updateRow(i);
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		int threadAmount = thread::hardware_concurrency();
		int rowsPerThread = m_pixel_size.y / threadAmount;

		vector<thread> threads;
		threads.reserve(threadAmount);

		for (int i = 0; i < threadAmount; i++)
		{
			int start = i * rowsPerThread;
			int end = (i == threadAmount - 1) ? m_pixel_size.y : (i + 1) * rowsPerThread;
			threads.emplace_back(startThread, this, start, end);
		}
		for (auto& thread : threads) thread.join();
	}
	m_state = State::DISPLAYING;
}
void ComplexPlane::zoomIn()
{
	m_plane_center = m_mouseLocation;
	m_zoomCount++;
	float x = (float)BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = (float)BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(x, y);
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_plane_center = m_mouseLocation;
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(x, y);
	m_state = State::CALCULATING;
}