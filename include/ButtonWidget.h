#ifndef SFML_BASE_WIDGETS_BUTTONWIDGET_H
#define SFML_BASE_WIDGETS_BUTTONWIDGET_H

#include "BaseWidget.h"
#include <string>

namespace sfml { namespace base {

class ButtonWidget : public BaseWidget {
public:
    ButtonWidget();
    ButtonWidget(const std::string &text);
    ButtonWidget(const std::string &text, DrawStateColorMapping background, DrawStateColorMapping foreground);

    float getHeight();
    void setForegroundColors(DrawStateColorMapping foreground);
    void setBackgroundColors(DrawStateColorMapping background);
    void setText(const std::string &text);
    std::string getText();
    void draw(sf::View* v, sf::RenderWindow &w) override;
    bool delegateEvent(sf::RenderWindow& window, sf::Event& event, sf::View* view) override;
    void setClickedListener(std::function<void()> listener);

    virtual void setSize(sf::Vector2f size) override;

    void setTextAlign(TextAlign align);

    virtual sf::FloatRect globalBounds() override;

    virtual void onDrawStateChanged(DrawState oldState, DrawState newState) override;
private:
    void init();
    void reposition();

    sf::Text m_label;
    sf::RectangleShape m_background;

    // TODO: Make a class to represent this? (or a struct or something)
    DrawStateColorMapping m_stateForegroundColors;
    DrawStateColorMapping m_stateBackgroundColors;

    std::function<void()> m_listener{nullptr};

    TextAlign m_textAlign{ALIGN_CENTER};
};

}}


#endif //SFML_BASE_WIDGETS_BUTTONWIDGET_H
