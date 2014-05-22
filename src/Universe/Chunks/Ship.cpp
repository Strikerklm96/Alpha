#include "Ship.h"
///#include "ShipField.h"
#include "ForceField.h"

using namespace std;

Ship::Ship() : Chunk()
{
    ShipData data;
    f_initialize(data);
}
Ship::Ship(const ShipData& sData) : Chunk(static_cast<ChunkData>(sData))
{
    f_initialize(sData);
}
Ship::~Ship()
{

}
void Ship::f_initialize(const ShipData& sData)
{


    /**temporary**/
    ForceFieldData data;
    data.shape = Shape::CIRCLE;
    data.isSensor = true;
    data.halfSize = b2Vec2(8, 8);
    data.density = 0;
    data.pBody = m_pBody;
    data.categoryBits = collide::CollisionCategory::Sensor;
    data.maskBits = collide::CollisionCategory::Projectile | collide::CollisionCategory::Sensor;

    ForceField* tempPtr = new ForceField(data);
    m_ModuleSPList.push_back(tr1::shared_ptr<Module>(tempPtr));
    m_SpecialPhysPList.push_back(tempPtr);
}