#include "debug_draw.h"

SDLDebugDraw::SDLDebugDraw(SDL_Renderer *renderer, const float & M2P) : m_renderer(renderer), M2P(M2P)
{

}

void SDLDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
  // Set the renderer color to the Box2D color
  SDL_SetRenderDrawColor(m_renderer, color.r * 255, color.g * 255, color.b * 255, SDL_ALPHA_OPAQUE);
  // Draw the polygon
  for (int i = 0; i < vertexCount - 1; i++)
  {
    int x1 = vertices[i].x * M2P;
    int y1 = vertices[i].y * M2P;
    int x2 = vertices[i + 1].x * M2P;
    int y2 = vertices[i + 1].y * M2P;
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
  }
  int x1 = vertices[vertexCount - 1].x * M2P;
  int y1 = vertices[vertexCount - 1].y * M2P;
  int x2 = vertices[0].x * M2P;
  int y2 = vertices[0].y * M2P;
  SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
  // Draw a line to close the polygon
  SDL_RenderDrawLine(m_renderer, x2, y2, vertices[1].x * M2P, vertices[1].y * M2P);
}

void SDLDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
  // Set the renderer color to the Box2D color
  SDL_SetRenderDrawColor(m_renderer, color.r * 255, color.g * 255, color.b * 255, SDL_ALPHA_OPAQUE);
  int SCREEN_HEIGHT = 720;
  // Draw the polygon
  for (int i = 0; i < vertexCount - 1; i++)
  {
    int x1 = vertices[i].x * M2P + 15;
    int y1 = vertices[i].y * M2P + 15;
    int x2 = vertices[i + 1].x * M2P + 15;
    int y2 = vertices[i + 1].y * M2P + 15;
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
  }
  int x1 = vertices[vertexCount - 1].x * M2P + 15;
  int y1 = vertices[vertexCount - 1].y * M2P + 15;
  int x2 = vertices[0].x * M2P + 15;
  int y2 = vertices[0].y * M2P + 15;
  SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
  // Draw a line to close the polygon
  SDL_RenderDrawLine(m_renderer, x2, y2, vertices[1].x * M2P + 15, vertices[1].y * M2P + 15);
}

void SDLDebugDraw::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color)
{
#if 0
	SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
		static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
	int x = static_cast<int>(center.x * 10);
	int y = static_cast<int>(center.y * 10);
	int r = static_cast<int>(radius * 10);
	for (int i = 0; i <= r; i++)
	{
		int j = static_cast<int>(sqrt(r * r - i * i));
		SDL_RenderDrawPoint(m_renderer, x + i, y + j);
		SDL_RenderDrawPoint(m_renderer, x + i, y - j);
		SDL_RenderDrawPoint(m_renderer, x - i, y + j);
		SDL_RenderDrawPoint(m_renderer, x - i, y - j);
	}
#endif
}

void SDLDebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
{
#if 0
	SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
		static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
	int x = static_cast<int>(center.x * 10);
	int y = static_cast<int>(center.y * 10);
	int r = static_cast<int>(radius * 10);
	for (int i = 0; i <= r; i++)
	{
		int j = static_cast<int>(sqrt(r * r - i * i));
		SDL_RenderDrawPoint(m_renderer, x + i, y + j);
		SDL_RenderDrawPoint(m_renderer, x + i, y - j);
		SDL_RenderDrawPoint(m_renderer, x - i, y + j);
		SDL_RenderDrawPoint(m_renderer, x - i, y - j);
	}
#endif
}

void SDLDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
  SDL_SetRenderDrawColor(m_renderer, static_cast<uint8_t>(color.r * 255), static_cast<uint8_t>(color.g * 255), static_cast<uint8_t>(color.b * 255), SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y));
}

void SDLDebugDraw::DrawTransform(const b2Transform &xf)
{
  b2Vec2 xAxis = xf.q.GetXAxis();
  b2Vec2 yAxis = xf.q.GetYAxis();
  b2Vec2 p1 = xf.p;
  b2Vec2 p2 = p1 + 0.4f * xAxis;
  b2Vec2 p3 = p1 + 0.4f * yAxis;
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x * 10), static_cast<int>(p1.y * 10),
                     static_cast<int>(p2.x * 10), static_cast<int>(p2.y * 10));
  SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
  SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x * 10), static_cast<int>(p1.y * 10),
                     static_cast<int>(p3.x * 10), static_cast<int>(p3.y * 10));
}

void SDLDebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
  SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
                         static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
  SDL_Rect rect = {
      static_cast<int>((p.x - size / 2.0f) * 10),
      static_cast<int>((p.y - size / 2.0f) * 10),
      static_cast<int>(size * 10),
      static_cast<int>(size * 10)};
  SDL_RenderFillRect(m_renderer, &rect);
}
