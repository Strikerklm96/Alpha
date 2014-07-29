#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "stdafx.h"
#include "Chunk.h"
#include "Projectile.h"
#include "UniversalContactListener.h"//END
#include "UniversalQueryCallback.h"
#include "DebugDraw.h"
#include "BedFinder.h"
#include "ProjectileAllocator.h"
#include "GraphicsComponentFactory.h"

#include "Decoration.h"

class Universe : public IOBase//everything that would be considered to be "real" such as a box, or a star in the background is in the Universe, everything else like HUD and menus are in OverlayManager
{
public:
    Universe();
    ~Universe();

    IOBase* getTarget(const std::string& targetName);
    IOBase* getTarget(unsigned int targetID);
    Chunk* getPhysTarget(const std::string& targetName);
    Chunk* getPhysTarget(unsigned int targetID);
    Decoration* getGfxTarget(const std::string& targetName);
    Decoration* getGfxTarget(unsigned int targetID);


    Chunk* getForwardPhys();//gets the next chunk element
    Chunk* getBackwardPhys();//gets the next backward chunk element


    b2World& getWorld();
    BedFinder& getBedFinder();
    ProjectileAllocator& getProjAlloc();
    GraphicsComponentFactory& getGfxCompFactory();


    void add(Chunk* pChunk);
    void add(Decoration* pDecor);


    void removeBack();
    bool removeTarget(std::string target);


    float physStep();
    void togglePause();
    float getTime() const;


    void draw();//draws everything thats drawable in universe
    void toggleDebugDraw();
protected:
private:
    UniversalContactListener m_contactListener;
    DebugDraw m_debugDraw;

    b2World m_physWorld;
    BedFinder m_bedFinder;
    ProjectileAllocator m_projAlloc;
    GraphicsComponentFactory m_gfxCompFactory;


    float m_pauseTime;
    float m_skippedTime;
    bool m_paused;
    bool m_normalDraw;

    int m_iterations;
    int m_maxIterations;
    float m_remainingTime;
    float m_timeStep;
    int m_velocityIterations;
    int m_positionIterations;

    std::vector<std::tr1::shared_ptr<Decoration> > m_gfxList; //all the objects that have only graphics
    std::vector<std::tr1::shared_ptr<Chunk> > m_physList;//all the objects that have physics, and maybe graphics
};

#endif // UNIVERSE_H
