#include "DebugDraw.h"
#include "globals.h"

#include "Angles.h"

DebugDraw::DebugDraw() : m_rWindow(game.getGameWindow())
{

    m_convex.setFillColor(sf::Color(0,200,0,64));
    m_convex.setOutlineColor(sf::Color(0,255,0,255));
    m_convex.setOutlineThickness(-1);

    m_circle.setFillColor(sf::Color(0,200,0,64));
    m_circle.setOutlineColor(sf::Color(0,255,0,255));
    m_circle.setOutlineThickness(-1);
}

DebugDraw::~DebugDraw()
{

}
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    m_convex.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        m_convex.setPoint(i, leon::b2Tosf<float>(vertices[i]));
    }
    m_rWindow.draw(m_convex);
}
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    m_circle.setRadius(radius*scale);
    m_circle.setPosition(leon::b2Tosf<float>(center));
    m_rWindow.draw(m_circle);
}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    m_circle.setOrigin(radius*scale, radius*scale);
    m_circle.setRadius(radius*scale);
    m_circle.setPosition(leon::b2Tosf<float>(center));
    m_rWindow.draw(m_circle);
}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}
void DebugDraw::DrawTransform(const b2Transform& xf)
{

}
void SetWindow(const sf::RenderWindow& rWindow)
{

}
