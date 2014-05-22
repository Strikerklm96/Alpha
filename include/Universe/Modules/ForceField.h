#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include "Module.h"

struct ForceFieldData : public ModuleData
{
    ForceFieldData() :
        ModuleData()
        {}
};

class ForceField : public Module
{
public:
    ForceField();
    ForceField(const ForceFieldData& data);
    virtual ~ForceField();

    virtual int startContact(void* other);
    virtual int endContact(void* other);

    virtual bool physUpdate();
protected:
private:
    virtual void f_initialize(const ForceFieldData& data);

    b2Body* m_targetBody;

    float m_strength;
    bool m_hasContact;

    std::map<b2Body*, int>::iterator m_it;
    b2Vec2 m_force;
    b2Vec2 m_ourCoords;
    b2Vec2 m_theirCoords;
    float m_distance;
    float m_theirMass;
    b2Vec2 m_direction;

    std::map<b2Body*, int> m_targets;
};

#endif // FORCEFIELD_H