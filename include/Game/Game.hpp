#ifndef GAME_H
#define GAME_H


#include "IOBase.hpp"
#include "OverlayManager.hpp"
#include "TextureAllocator.hpp"
#include "Universe.hpp"

class IOManager;
class ControlManager;

class Game// : public IOBase//holds a universe, OverlayManager, and IOManager, and other stuff
{
public:
    Game();
    ~Game();

    enum Status
    {
        Client,
        Server,
        Local,
        Quit,
    };
    //loop over our contents and do stuff
    //void load(stuff);//loads stuff from files, and puts it in the right places, how should we go about this???
    //void setAddresses();//go through our Couriers, find their targets, and set their addresses, so they don't have to search later
    Status run();
    Status local();
    Status client();
    Status server();
    void setStatus(Game::Status newStatus);
    IOBaseReturn input(IOBaseArgs);

    void loadWindow();
    void reloadWindow();

    float getTime() const;

    IOManager& getGameIOManager();
    sf::RenderWindow& getGameWindow();
    Universe& getGameUniverse();
    OverlayManager& getGameOverlayManager();
    TextureAllocator& getTextureAllocator();
    AnimationAllocator& getAnimationAllocator();

    sf::RenderTarget& getRenderTarget();



    sf::Shader m_blurShader;
    sf::Shader m_vecFieldShader;
    sf::Shader m_shader;

protected:
private:
    void f_load(const std::string& stuff);//told where to get blueprintsData and mapsData, and panelsData


    /**created first**/
    std::tr1::shared_ptr<AnimationAllocator> m_spAnimAlloc;
    std::tr1::shared_ptr<sf::RenderWindow> m_spWindow;///unfortunately TGUI keeps a pointer to this!!
    std::tr1::shared_ptr<IOManager> m_spIOManager;
    std::tr1::shared_ptr<TextureAllocator> m_spTexAlloc;
    std::tr1::shared_ptr<Universe> m_spUniverse;
    /**needs access to previous ones**/
    std::tr1::shared_ptr<OverlayManager> m_spOverlayManager;
    std::tr1::shared_ptr<ControlManager> m_spControlManager;

    Game::Status m_state;
    sf::Clock m_clock;
    sf::Image m_icon;
    sf::ContextSettings m_settings;

    std::tr1::shared_ptr<sf::Sprite> m_spRenderSprite;
    sf::RenderTexture m_renderTexture;
};

#endif // GAME_H







    /**
    DONT NEED IT ANYMORE
    //std::vector<Courier*> m_allCouriers;///this problem is so old we almost forgot about it
    //IN order to avoid IOManager having to search for objects during runtime, it will find them
    //at load time, and give them pointers to the IOBase part of the target, so later, it can just
    // use the pointer and send the message instantly
    //the problem is, what if that object got deleted...
    //that is solved by our friend: shared_ptr
    //by giving the courier a shared_ptr, even though the object was told to be deleted, it wont delete until
    //all shared_ptr's have tried to delete it
    so a deleted object will actually sit in memory, then it will get the message, and destroy itself
    **/
