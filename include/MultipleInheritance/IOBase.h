#ifndef IOBASE_H
#define IOBASE_H

#include "stdafx.h"
#include "Condition.h"

/*HOW IO WORKS
When some event happens, whether its a player presssing a button, or a condition being met, a signal needs to sent to the target to tell it what to do.
All messages, regardless of their origin are sent to IOManager, so any object that wants to ever send a message needs to know about the IOManager. IOManager needs to know
about Universe and OverlayManager, so it can make things happen in them, and then objects inside of OverlayManager and Universe need to know about IOManager for reasons we just talked about.
In addition, Universe and OverlayManager need to have the input function so buttons and world events can call functions directly on eachother.
*/

class IOManager;
class IOBase;

struct IOBaseData
{
    std::string type;
    std::string name;
};
class IOBase//base class inherited by literally everything, that way objects can always communicate
{
public:
    IOBase();
    IOBase(const IOBaseData& data);
    virtual ~IOBase();


    virtual IOManager& getIOManager();
    void setName(const std::string& name);//sets the name of this entity
    const std::string& getName() const;//gets the name of this entity
    unsigned int getID() const;//gets the name of this entity


    virtual void damage(int damage);
    virtual void input_1(const std::string& rInput);
    virtual void input_2(const std::string& rInput);
    virtual void input_3(const std::string& rInput);
    virtual void input_4(const std::string& rInput);
    virtual void input_5(const std::string& rInput);
    virtual void input_6(const std::string& rInput);
    virtual void input_7(const std::string& rInput);
    virtual void input_8(const std::string& rInput);
    virtual void input_9(const std::string& rInput);
    virtual void input_10(const std::string& rInput);
protected:
    friend class Universe;
    void f_setID(unsigned int newID);//sets the name of this entity

    std::string m_type;//type of object that we are
    std::string m_name;//used by IO manager to locate specific named objects
    unsigned int m_ID;

    static IOManager& m_rIOManager;///should we be using static?
private:
};

#endif // IOBASE_H
