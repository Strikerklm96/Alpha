#ifndef PANEL_H
#define PANEL_H

#include <WidgetBase.h>

namespace leon
{

struct PanelData : public WidgetBaseData
{
    PanelData() :
        WidgetBaseData(),
        backgroundColor(leon::defaultBackgroundColor)
    {}
    sf::Color backgroundColor;
};

class Panel : public WidgetBase
{
public:
    Panel(tgui::Gui& gui);
    Panel(tgui::Gui& gui, const PanelData& data);///menubar struct constructor
    Panel(tgui::Container& container);
    Panel(tgui::Container& container, const PanelData& data);
    ~Panel();

    void toggleActive(const std::string& target);/**enable disable**/
    void toggleShow(const std::string& target);/**sleep wake**/

    void add(std::tr1::shared_ptr<WidgetBase> sp_widget);

protected:
    virtual void callback(const tgui::Callback& callback);
private:
    virtual void f_initialize(const PanelData& data);
    std::vector<std::tr1::shared_ptr<WidgetBase> > m_widgetList;
    tgui::Panel::Ptr m_pPanel;
};
}

#endif // PANEL_H