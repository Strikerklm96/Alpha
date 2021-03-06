#include "Chunk.hpp"
#include "globals.hpp"

#include "Intelligence.hpp"
#include "Sort.hpp"
#include "Convert.hpp"

#include "GModule.hpp"
#include "Module.hpp"

#include "Armor.hpp"
#include "ForceField.hpp"
#include "ForceFieldCore.hpp"
#include "Thruster.hpp"
#include "Weapon.hpp"

using namespace std;


Chunk::Chunk(const ChunkData& rData) : IOBase(static_cast<IOBaseData>(rData))
{
    m_pTiles = dynamic_cast<MultiTileMap*>(game.getGameUniverse().getGfxCompFactory().generate(rData.tileData));

    m_spLinker.reset(new Link<Chunk, Intelligence>(this));
    m_spZoomPool.reset(new ZoomPool(m_pIOComponent->getEventerPtr(), 0, rData.startMaxZoom, rData.startMinZoom));
    m_spEnergyPool.reset(new EnergyPool(m_pIOComponent->getEventerPtr(), 0, rData.startMaxEnergy));
    m_spAmmoGroup.reset(new AmmoGroup(rData.ammoGrouping));

    m_bodyDef.bullet = rData.isBullet;
    m_bodyDef.type = rData.bodyType;
    m_bodyDef.position = rData.position;
    m_controlEnabled = rData.controlEnabled;

    m_pBody = game.getGameUniverse().getWorld().CreateBody(&m_bodyDef);
    m_pBody->SetUserData(this);

    m_awake = true;//regardless, set us to be awake
    if(!rData.awake)//if it should be asleep
        sleep();//then cleanly put it to sleep
}
Chunk::~Chunk()/**Don't destroy us in the middle of a physics step!**/
{
    game.getGameUniverse().getWorld().DestroyBody(m_pBody);
    m_pTiles->free();
}


/**GET MODULES**/
GModule* Chunk::getGModule(const std::string& targetName)
{
    for(vector<tr1::shared_ptr<GModule> >::const_iterator it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_pIOComponent->getName() << "\":[" << m_pIOComponent->getID() << "]";
    ///ERROR LOG
    return NULL;
}
Module* Chunk::getModule(const std::string& targetName)
{
    for(vector<tr1::shared_ptr<Module> >::const_iterator it = m_ModuleSPList.begin(); it != m_ModuleSPList.end(); ++it)
    {
        if((*it)->getName() == targetName)
            return &(**it);
    }
    cout << "\nTarget " << targetName << " not found in chunk \"" << m_pIOComponent->getName() << "\":[" << m_pIOComponent->getID() << "]";
    ///ERROR LOG
    return NULL;
}
IOBase* Chunk::getIOBase(const std::string& targetName)
{
    IOBase* ptr = getGModule(targetName);
    if(ptr != NULL)
        return ptr;

    return getModule(targetName);
}


/**ADD MODULES**/
GModule* Chunk::add(const vector<tr1::shared_ptr<const GModuleData> >& rDataList)
{
    GModule* ptr;
    for(auto it_data = rDataList.begin(); it_data != rDataList.end(); ++it_data)
    {
        ptr = (*it_data)->generate(this);
        InsertPtrVector(m_GModuleSPList, &IOBase::getID, tr1::shared_ptr<GModule>(ptr));
        m_pTiles->add(ptr);///HERE IS WHERE WE WOULD give it a graphics COMPONENT, instead of us as a derived pointer from which it gets the base type
    }

    return ptr;
}
Module* Chunk::add(const vector<tr1::shared_ptr<const ModuleData> >& rDataList)
{
    Module* ptr;
    for(auto it_data = rDataList.cbegin(); it_data != rDataList.cend(); ++it_data)
    {
        ptr = (*it_data)->generate(this);
        InsertPtrVector(m_ModuleSPList, &IOBase::getID, tr1::shared_ptr<Module>(ptr));
    }

    return ptr;
}
Weapon* Chunk::add(const WeaponData& rData)
{
    Weapon* ptr = new Weapon(rData);
    m_WeaponSPList.push_back(std::tr1::shared_ptr<Weapon>(ptr));
    return ptr;
}


/**PHYSICS**/
int Chunk::startContact(PhysicsBase* other)
{
    (void)other;//shutup the compiler about unused
    return 0;
}
int Chunk::endContact(PhysicsBase* other)
{
    (void)other;//shutup the compiler about unused
    return 0;
}
int Chunk::preSolveContact(PhysicsBase* other)
{
    (void)other;//shutup the compiler about unused
    return 0;
}
int Chunk::postSolveContact(PhysicsBase* other)
{
    (void)other;//shutup the compiler about unused
    return 0;
}
b2Body* Chunk::getBody()
{
    return m_pBody;
}
void Chunk::physUpdate()//loop over all the special physics objects
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->physUpdate();
    }
    for(auto it = m_ModuleSPList.begin(); it != m_ModuleSPList.end(); ++it)
    {
        (*it)->physUpdate();
    }
}
void Chunk::sleep()
{
    if(m_awake)//if we aren't already sleeping!
    {
        m_oldPos = m_pBody->GetPosition();//get our current data
        m_oldAngle = m_pBody->GetAngle();//radians

        m_pBody->SetActive(false);//remove from calculation
        m_pBody->SetAwake(false);//remove from updating
        toggleControl(false);

        m_pBody->SetLinearVelocity(b2Vec2(0,0));//cancel any movement
        m_pBody->SetAngularVelocity(0.0f);
        m_pBody->SetTransform(game.getGameUniverse().getBedFinder().getSleepPosition(), 0);//request new position from bedFinder
        m_awake = false;
        m_pTiles->setVisibility(false);
    }
}
void Chunk::wake()
{
    if(not m_awake)//if we aren't awake
    {
        game.getGameUniverse().getBedFinder().free(m_pBody->GetPosition());

        m_pBody->SetActive(true);
        m_pBody->SetAwake(true);//remove from updating

        m_pBody->SetTransform(m_oldPos, m_oldAngle);//move us//radians
        toggleControl(true);
        m_awake = true;
        m_pTiles->setVisibility(true);
    }
    else
    {
        cout << "\nWake Failed";
        ///error log
    }
}
void Chunk::wake(const b2Vec2& pos, float angle, const b2Vec2& velocity, float angVel)//box2d uses radians
{
    if(not m_awake)//if we aren't awake
    {
        game.getGameUniverse().getBedFinder().free(m_pBody->GetPosition());

        m_pBody->SetActive(true);
        m_pBody->SetAwake(true);

        m_pBody->SetTransform(pos, angle);//radians
        m_pBody->SetLinearVelocity(velocity);
        m_pBody->SetAngularVelocity(angVel);
        toggleControl(true);
        m_awake = true;
        m_pTiles->setVisibility(true);
    }
    else
    {
        cout << "\nWake Failed";
        ///error log
    }
}
bool Chunk::isAwake() const
{
    return m_awake;
}


/**INPUT**/
void Chunk::primary(const b2Vec2& coords)
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->primary(coords);
    }
}
void Chunk::secondary(const b2Vec2& coords)
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->secondary(coords);
    }
}
void Chunk::aim(const b2Vec2& coords)
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->aim(coords);
    }
}
void Chunk::up()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->up();
    }
}
void Chunk::down()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->down();
    }
}
void Chunk::left()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->left();
    }
}
void Chunk::right()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->right();
    }
}
void Chunk::rollLeft()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->rollLeft();
    }
}
void Chunk::rollRight()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->rollRight();
    }
}
void Chunk::special_1()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->special_1();
    }
}
void Chunk::special_2()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->special_2();
    }
}
void Chunk::special_3()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->special_3();
    }
}
void Chunk::special_4()
{
    for(auto it = m_GModuleSPList.begin(); it != m_GModuleSPList.end(); ++it)
    {
        (*it)->special_4();
    }
}




/**CONTROL**/
Link<Chunk, Intelligence>& Chunk::getLinker()
{
    return *m_spLinker;
}
void Chunk::toggleControl(bool state)//will or wont accept inputs from controllers
{
    m_controlEnabled = state;
}
bool Chunk::isControlEnabled() const
{
    return m_controlEnabled;
}



/**Variables**/
ZoomPool& Chunk::getZoomPool()
{
    return *m_spZoomPool;
}
std::tr1::shared_ptr<ZoomPool> Chunk::getZoomPoolSPtr()
{
    return m_spZoomPool;
}
EnergyPool& Chunk::getEnergyPool()
{
    return *m_spEnergyPool;
}
std::tr1::shared_ptr<EnergyPool> Chunk::getEnergyPoolSPtr()
{
    return m_spEnergyPool;
}
AmmoGroup& Chunk::getAmmoGroup()
{
    return *m_spAmmoGroup;
}
    std::tr1::shared_ptr<AmmoGroup>  Chunk::getAmmoGroupSPtr()
    {
            return m_spAmmoGroup;
    }

/**GRAPHICS**/
void Chunk::gfxUpdate()
{
    if(m_awake)///THIS PROBABLY SHOULDN'T BE HERE ANYMORE
    {
        auto it_end = m_GModuleSPList.end();
        for(auto it = m_GModuleSPList.begin(); it != it_end; ++it)
        {
            (*it)->animate();
        }

        m_pTiles->setPosition(m_pBody->GetPosition());
        m_pTiles->setRotation(m_pBody->GetAngle());
        m_pTiles->setVelocity(m_pBody->GetLinearVelocity());
    }
}



/**IO SYSTEM**/
IOBaseReturn Chunk::input(IOBaseArgs)
{
    if(rCommand == "message")
    {
        std::string message;
        if(rInput >> message)
            std::cout << std::endl << m_pIOComponent->getName() << " has " << m_GModuleSPList.front()->getHealth() << " health, and received message: [" << message << "].";
        else
        {
            std::cout << "\nError in data extraction in input in GModule." << FILELINE;
            ///ERROR LOG
        }
    }
    else
    {
        std::cout << "\nError: [" << rCommand << "] was not recognized as a command." << FILELINE;
        ///ERROR LOG
    }
}












/*
void Chunk::setGroupIndex(int group)
{
    ///ERROR LOG
    cout << "\nWtf are you doing??";
    //loop over fixtures
    for (b2Fixture* fix = m_pBody->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Filter filter = fix->GetFilterData();
        filter.groupIndex = group;
        fix->SetFilterData(filter);
    }
}*/
