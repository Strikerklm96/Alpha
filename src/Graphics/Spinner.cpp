#include "Spinner.hpp"
#include "stdafx.hpp"

#include "Convert.hpp"
#include "GModule.hpp"

Spinner::Spinner(const SpinnerData& rData) : m_decor(rData.decorData)
{
    m_spinnerAxisOffset = rData.spinnerOffset;
    m_spinRate = leon::degToRad(rData.spinRate);
    m_currentRelativeRotation = 0.0f;
}
Spinner::~Spinner()
{

}
void Spinner::update(const b2Vec2& rCenterOfParent, float radiansCCW)
{
    m_currentRelativeRotation += m_spinRate*m_timer.getTimeElapsed();

    b2Vec2 newPos;
    newPos.x = cos(-radiansCCW)*(m_spinnerAxisOffset.x) + sin(-radiansCCW)*(m_spinnerAxisOffset.y);
    newPos.y = -sin(-radiansCCW)*(m_spinnerAxisOffset.x) + cos(-radiansCCW)*(m_spinnerAxisOffset.y);
    newPos += rCenterOfParent;

    m_decor.setPosition(newPos);
    m_decor.setRotation(m_currentRelativeRotation+radiansCCW);
   // std::cout << "(" << newPos.x << "," << newPos.y << ")";
}