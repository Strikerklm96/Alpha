#ifndef DCHUNK_H
#define DCHUNK_H

#include "stdafx.h"
#include "MultiTileMap.h"
#include "ForceField.h"///dont need this??

class GModule;
struct GModuleData;
class Module;
struct ModuleData;
class Intelligence;

struct ChunkData : public IOBaseData//initialized
{
    ChunkData() :
        IOBaseData(),
        bodyType(def::cnk::defaultBodyType),
        position(def::cnk::defaultPosition),
        isBullet(def::cnk::defaultIsBullet),
        maxZoom(def::cnk::defaultMaxZoom),
        minZoom(def::cnk::defaultMinZoom),
        controlEnabled(def::cnk::defaultCntrlEnabled)
        {}

    b2BodyType bodyType;
    b2Vec2 position;
    bool isBullet;
    float maxZoom;
    float minZoom;
    bool controlEnabled;
};

class Chunk : public IOBase
{
public:
    Chunk();
    Chunk(const ChunkData& data);
    virtual ~Chunk();//Don't destroy us in the middle of a physics step
    ///Chunk(const Chunk& old);///should this exist?

    virtual b2Body* getBody();

    virtual GModule* getGModule(const std::string& targetName);
    virtual Module* getModule(const std::string& targetName);
    virtual IOBase* getIOBase(const std::string& targetName);

  ///  virtual void add(std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList);
    virtual void add(std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList, std::vector<b2Vec2>& vertices);//we only call this once!
    virtual void add(std::vector<std::tr1::shared_ptr<ModuleData> >& data);//we only call this once!

    virtual void draw();
    virtual void physUpdate();

    /**IO-SYSTEM**/
    virtual void enableControl();//will or wont accept inputs from controllers
    virtual void disableControl();

    virtual void sleep();//sets body to sleep, sets all velocities to 0, and goes to coord args
    virtual void wake();
    virtual void wake(const b2Vec2& newPos, const float angle, const b2Vec2& velocity, const float angVel);


    /**INPUT**/
    virtual void primary(sf::Vector2f coords);
    virtual void secondary(sf::Vector2f coords);
    virtual void aim(sf::Vector2f coords);
    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    virtual void rollLeft();
    virtual void rollRight();
    virtual void special_1();
    virtual void special_2();
    virtual void special_3();
    virtual void special_4();

    virtual float getMaxZoom() const;
    virtual float getMinZoom() const;

    /**CONTROL**/
    Intelligence* getController() const;
    bool hasController() const;
    void linkControl(Intelligence* controller);
    void breakControl();

    /**CONST OVERLOADS**/
    virtual b2Body* getBody() const;
    virtual const b2BodyDef& getBodyDef() const;
    virtual const std::vector<std::tr1::shared_ptr<GModule> >& getGModuleSPList() const;
    virtual const std::vector<std::tr1::shared_ptr<Module> >& getModuleSPList() const;
    virtual const MultiTileMap& getTiles() const;

    /**OVERRIDE**/
    virtual void input_1(sf::Packet& rInput);

protected:
    sf::RenderWindow& m_rWindow;
    b2World& m_rPhysWorld;

    float m_maxZoom;///used by controller to limit zoom levels maybe this should be somewhere else?
    float m_minZoom;

    b2Body* m_pBody;
    b2BodyDef m_bodyDef;
    MultiTileMap m_tiles;

    std::vector<std::tr1::shared_ptr<GModule> > m_GModuleSPList;
    std::vector<std::tr1::shared_ptr<Module> > m_ModuleSPList;
    std::vector<PhysicsBase*> m_SpecialPhysPList;//these are objects that need to do special physics operations every tick

    float m_accel, m_torque;///move these to a derivative of chunk

private:
    float f_findRadius(std::vector<std::tr1::shared_ptr<GModuleData> >& rDataList);//finds the top/bottom left, bottom
    virtual void f_initialize(const ChunkData& data);

    friend class Intelligence;
    void f_forgetController();//CONTROL
    void f_setController(Intelligence* controller);
    Intelligence* m_pController;//this is a pointer to our controller
    bool m_hasController;
    bool m_controlEnabled;

    b2Vec2 m_oldPos;
    float m_oldAngle;
};

#endif // DCHUNK_H
