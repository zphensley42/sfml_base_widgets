#include "HContainer.h"

namespace sfml { namespace base {

void HContainer::draw(sf::View *v, sf::RenderWindow &w) {
    for(auto& child : m_children) {
        child->draw(v, w);
    }
}

bool HContainer::delegateEvent(sf::RenderWindow& window, sf::Event &event, sf::View* view) {
    for(auto& child : m_children) {
        if(child->delegateEvent(window, event, view)) {
            return true;
        }
    }
    return false;
}

void HContainer::setSize(sf::Vector2f size) {
    BaseWidget::setSize(size);  // width is flexible and updated on layout (we don't force items to fill only this size currently)
    // TODO: Special sizes for wrap content or forced size? (i.e. if -1 then allow to grow but if > 0 then force the size and 'cut off' items outside of it somehow)
    layoutChildren();
}
void HContainer::setPosition(sf::Vector2f position) {
    BaseWidget::setPosition(position);
    layoutChildren();
}

void HContainer::layoutChildren() {
    float runningX = 0;
    auto gb = globalBounds();
    float maxH = gb.height;
    for(auto& child : m_children) {
        // TODO: The below is failing b/c button widget doesn't know its proper size until draw() is called once
        auto cBG = child->globalBounds();
        if(runningX > 0) {
            runningX += m_hSpacing;
        }
        child->setPosition({gb.left + runningX, gb.top + cBG.top});
        runningX += cBG.width;

        if(cBG.height > maxH) {
            maxH = cBG.height;
        }
    }
    m_bounds.width = runningX;
    if(maxH != m_bounds.height) {
        m_bounds.height = maxH;
    }
}

}}