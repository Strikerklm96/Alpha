#ifndef IOCOMPONENT_H
#define IOCOMPONENT_H

#include "defaults.hpp"
#include "Courier.hpp"
#include "ActiveEventer.hpp"

class IOComponent
{
public:
    IOComponent(unsigned int id, IOManager& manager);
    virtual ~IOComponent();

    void free();
    void setOwner(IOBase* pOwner);
    IOBase* getOwner();

    unsigned int getID() const;

    const std::string& getName() const;
    void setName(const std::string& name);

    ActiveEventer* getEventerPtr();
    void resetEventer();//used in Game::Game() to reset some pointers that otherwise get messed up

    IOBaseReturn input(IOBaseArgs);//called for any input
protected:
private:
    IOBase* m_pOwner;

    unsigned int m_ID;
    std::string m_name;//used by IO manager to locate specific named objects

    std::tr1::shared_ptr<ActiveEventer> m_spEventer;
};

#endif // IOCOMPONENT_H
