#ifndef REACTOR_H
#define REACTOR_H

#include "GModule.hpp"
#include "ValueChanger.hpp"

struct ReactorData;
/**produces energy for our energy pool**/
class Reactor : public GModule
{
public:
    Reactor(const ReactorData& rData);
    virtual ~Reactor();

    bool physUpdate();

protected:
private:
    ValueChanger<T_Energy> m_reactorCore;
};

struct ReactorData : public GModuleData
{
    ReactorData() :
        GModuleData(),
        energyProduceRate(5)
    {
        type = ClassType::REACTOR;
        texName = "textures/reactor/reactor.png";
        animationFileName = "textures/reactor/reactor.acfg";
    }

    T_Energy energyProduceRate;

    virtual GModule* generate(Chunk* pChunk) const
    {
        ReactorData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Reactor(mutableCopy);
    }
};

#endif // REACTOR_H
