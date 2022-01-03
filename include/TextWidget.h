#ifndef GWIDI_IMPORTER_TEXTWIDGET_H
#define GWIDI_IMPORTER_TEXTWIDGET_H

#include "BaseWidget.h"
#include <string>

namespace sfml { namespace base {

class TextWidget : public BaseWidget {
public:
    TextWidget();
    explicit TextWidget(const std::string& text);

    void draw(sf::View* v, sf::RenderWindow &w) override;
    bool delegateEvent(sf::RenderWindow& window, sf::Event& event, sf::View* view) override;

    virtual void setSize(sf::Vector2f size) override;
    virtual void setPosition(sf::Vector2f position) override;
    virtual sf::FloatRect globalBounds() override;
    virtual void onDrawStateChanged(DrawState oldState, DrawState newState) override;
    std::string getText();
    void setText(const std::string &text, unsigned int size = 16, sf::Color color = sf::Color::White);
    void setTextAlign(TextAlign align);

private:
    void init();
    void reposition();

    sf::Text m_label;
    sf::RectangleShape m_background;
    TextAlign m_textAlign{ALIGN_CENTER};
};

}}


#endif //GWIDI_IMPORTER_TEXTWIDGET_H
