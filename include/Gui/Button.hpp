#ifndef BUTTON_H
#define BUTTON_H

#include "WidgetBase.hpp"

namespace leon
{
struct ButtonData : public WidgetBaseData
{
    ButtonData() :
        WidgetBaseData(),
        buttonText(defaults::gui::buttonText)
    {
        type = ClassType::BUTTON;
    }

    std::string buttonText;
};


class Button : public WidgetBase
{
public:
    Button(tgui::Gui& gui, const ButtonData& data);///menubar struct constructor
    Button(tgui::Container& container, const ButtonData& data);
    virtual ~Button();

    /**IO**/
    virtual IOBaseReturn input(IOBaseArgs);
protected:
    virtual void f_callback(const tgui::Callback& callback);
    virtual void f_MouseEntered();
    virtual void f_MouseLeft();
    virtual void f_LeftMouseClicked();

private:
    virtual void f_initialize(const ButtonData& data);

    tgui::Button::Ptr m_pButton;//pointer to our button in the gui
};
}
#endif // BUTTON_H
