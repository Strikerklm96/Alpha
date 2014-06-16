#ifndef ARMOR_H
#define ARMOR_H

#include "GModule.h"

struct ArmorData : public GModuleData
{
    ArmorData() :
        GModuleData()
    {
        type = ClassType::ARMOR;
        categoryBits = Category::ShipModule;
        maskBits = Mask::ShipModuleNorm;
        armor = 500;
        texName = "textures/armor/armor.png";
    }

};

class Armor : public GModule
{
public:
    Armor();
    Armor(const ArmorData& data);
    virtual ~Armor();

protected:
private:
    void f_initialize(const ArmorData& data);

};

#endif // ARMOR_H