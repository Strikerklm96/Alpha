#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Module.h"
#include "SpecialPhys.h"

struct ForceFieldData
{
    ForceFieldData(){moduleBaseData.physicsData.isSensor = true;}
    ModuleData moduleBaseData;
};

class ForceField : public Module, public SpecialPhys
{
public:
    ForceField(ForceFieldData& data);
    virtual ~ForceField();

    virtual bool physUpdate();
protected:
private:
    PhysicsBase* m_target;//for convienience;
    b2Fixture* m_targetFixture;
    b2ContactEdge* m_contactList;
    bool m_hasContact;
};

#endif // FORCEFIELD_H