#include <MultipleInheritance/GraphicsBase.h>

#include <globals.h>

using namespace std;

GraphicsBase::GraphicsBase(const GraphicsBaseData& rData, const b2Vec2& rHalfSize, const b2Vec2& rOffset)
: m_tilePos(rOffset.x, rOffset.y), m_color(rData.color), m_tileSize(rHalfSize.x*2, rHalfSize.y*2)///IS M_TILEPOS CORRECTLY SET?
{
    m_pVertex = NULL;
    m_texTileSize = rData.texTileSize;
    m_texTile = rData.texTile;
    m_texName = rData.texName;
}
GraphicsBase::~GraphicsBase()
{
}
void GraphicsBase::setTexName(const string& texName)
{
    m_texName = texName;
}
const string GraphicsBase::getTexName() const
{
    return m_texName;
}
void GraphicsBase::setVertex(sf::Vertex* pVertex)///verify pointer integrity
{
    m_pVertex = pVertex;
    setColor(m_color);
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}
const sf::Vertex* GraphicsBase::getVertex() const///verify pointer integrity
{
    return m_pVertex;
}
void GraphicsBase::setTilePos(const sf::Vector2f& rTilePos)///THIS IS GOING WRONG SOMEHOW
{
    m_tilePos = rTilePos;
    if (m_pVertex != NULL)
    {
        m_pVertex[0].position = sf::Vector2f(scale*m_tilePos.x, scale*m_tilePos.y);//0
        m_pVertex[1].position = sf::Vector2f(scale*(m_tilePos.x+m_tileSize.x), scale*m_tilePos.y);//1
        m_pVertex[2].position = sf::Vector2f(scale*(m_tilePos.x+m_tileSize.x), scale*(m_tilePos.y+m_tileSize.y));//2
        m_pVertex[3].position = sf::Vector2f(scale*m_tilePos.x, scale*(m_tilePos.y+m_tileSize.y));//3
        return;
    }
    else
        cout << "\nWARNING: GraphicsBase::setTilePos()";//debug
}
const sf::Vector2f& GraphicsBase::getTilePosition() const
{
    return m_tilePos;
}
void GraphicsBase::setTexTile(const sf::Vector2f& rTexTile)
{
    if (m_pVertex != NULL)
    {
        m_texTile = rTexTile;
        m_pVertex[0].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y));
        m_pVertex[1].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y));
        m_pVertex[2].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x+1), m_texTileSize.y*(m_texTile.y+1));
        m_pVertex[3].texCoords = sf::Vector2f(m_texTileSize.x*(m_texTile.x), m_texTileSize.y*(m_texTile.y+1));
        return;
    }
    else
        cout << "\nWARNING: GraphicsBase::setTexTile()";//debug
}
const sf::Vector2f& GraphicsBase::getTexTile() const
{
    return m_texTile;
}
void GraphicsBase::setTileSize(const sf::Vector2f& rTileSize)
{
    m_tileSize = rTileSize;
    setTexTile(m_texTile);
    setTilePos(m_tilePos);
}
const sf::Vector2f& GraphicsBase::getTileSize() const
{
    return m_tileSize;
}
void GraphicsBase::setColor(const sf::Color& rColor)
{
    m_color = rColor;
    if(m_pVertex != NULL)
    {
        m_pVertex[0].color = rColor;
        m_pVertex[1].color = rColor;
        m_pVertex[2].color = rColor;
        m_pVertex[3].color = rColor;
    }
    else
        cout << "\nWARNING: GraphicsBase::setColor()";//debug
}
const sf::Color& GraphicsBase::getColor() const
{
    if(m_pVertex != NULL)
        return m_pVertex[0].color;
    else
    {
        cout <<"\nWarning: GraphicsBase::getColor()";//debug
        return sf::Color::White;
    }
}
void GraphicsBase::setDispPri(const int dispPri)
{
    m_dispPri = dispPri;
}
const int GraphicsBase::getDispPri() const
{
    return m_dispPri;
}

/**Const Overloads**/
