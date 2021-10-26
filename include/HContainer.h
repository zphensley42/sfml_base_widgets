#ifndef GWIDI_IMPORTER_HCONTAINER_H
#define GWIDI_IMPORTER_HCONTAINER_H

#include "BaseWidget.h"

namespace sfml { namespace base {

class HContainer : public BaseWidget {
public:
    // TODO: Add a background to the container?
    // TODO: Add alignment (i.e. center, left, right) that is used to space items with dummy space
    HContainer() = default;
    ~HContainer() = default;

    void draw(sf::View* v, sf::RenderWindow &w) override;
    bool delegateEvent(sf::RenderWindow& window, sf::Event &event, sf::View* view) override;

    virtual void setSize(sf::Vector2f size) override;
    virtual void setPosition(sf::Vector2f position) override;

    inline void setSpacing(float spacing) {
        m_hSpacing = spacing;
        layoutChildren();
    }
    void layoutChildren();
private:
    float m_hSpacing{0};
};

}}


#endif //GWIDI_IMPORTER_HCONTAINER_H
