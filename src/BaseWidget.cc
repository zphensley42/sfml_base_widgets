#include "BaseWidget.h"

namespace sfml { namespace base {

void BaseWidget::setSize(sf::Vector2f size) {
    m_bounds.width = size.x;
    m_bounds.height = size.y;
}

void BaseWidget::setPosition(sf::Vector2f position) {
    m_bounds.left = position.x;
    m_bounds.top = position.y;
}

FocusManager& FocusManager::instance() {
    static FocusManager s;
    return s;
}

bool FocusManager::delegateEventToFocusedWidget(sf::Event &event) {
    if(hasFocusedWidget()) {
        m_focused->delegateEvent(event);
        return true;
    }
    return false;
}

}}