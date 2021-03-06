#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "GModule.hpp"
#include "CapacityChanger.hpp"
#include "RadialMeter.hpp"

struct CapacitorData;

class Capacitor : public GModule
{
public:
    Capacitor(const CapacitorData& rData, std::tr1::shared_ptr<EnergyPool> spEpool);
    virtual ~Capacitor();

protected:
    void animatePreHook();
    void enablePostHook();
    void disablePostHook();

private:
    RadialMeter m_energyFill;

    CapacityChanger<T_Energy> m_capacity;
    std::tr1::shared_ptr<EnergyPool> m_spEnergyPool;
};

struct CapacitorData : public GModuleData
{
    CapacitorData() :
        GModuleData(),
        comesWith(50),
        energyStorage(100)
    {
        type = ClassType::CAPACITOR;
        texName = "textures/capacitor/capacitor.png";
        animationFileName = "textures/capacitor/capacitor.acfg";
    }

    T_Ammo comesWith;
    T_Energy energyStorage;
    RadialMeterData fillData;

    virtual GModule* generate(Chunk* pChunk) const
    {
        CapacitorData mutableCopy(*this);
        mutableCopy.pBody = pChunk->getBody();
        mutableCopy.pChunk = pChunk;
        return new Capacitor(mutableCopy, pChunk->getEnergyPoolSPtr());
    }
};
#endif // CAPACITOR_H
