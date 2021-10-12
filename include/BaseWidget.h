#ifndef GWIDI_SFML_BASEWIDGET_H
#define GWIDI_SFML_BASEWIDGET_H

#include <SFML/Graphics.hpp>

namespace sfml { namespace base {

class BaseWidget {
public:
    enum DrawState {
        BW_DS_NONE = 0,
        BW_DS_HOVERED,
        BW_DS_PRESSED,
        BW_DS_ACTIVATED,
        BW_DS_DISABLED,
    };
    BaseWidget() = default;
    virtual ~BaseWidget() = default;

    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);

    // TODO: Need to determine how to handle notifying this is the focused view now for when we click into this view (so that we can handle things like dragging / mouse up
    // TODO: but specifically to this view).
    // TODO: Ideas: Callback into parent (requires parent to know / handle it); Call into manager held in library (no need for external visibility other than manager's interface,
    // TODO: which should generally not be needed); Other?
    virtual void delegateEvent(sf::Event &event) {}

    inline sf::FloatRect& bounds() {
        return m_bounds;
    }

    virtual void draw(sf::View* v, sf::RenderWindow &w) {}
protected:
    DrawState m_drawState{BW_DS_NONE};
    sf::FloatRect m_bounds;

    bool m_drawn{false};
};

struct DrawStateColorMapping {
    sf::Color none;
    sf::Color hovered;
    sf::Color pressed;
    sf::Color activated;
    sf::Color disabled;

    inline sf::Color& forState(BaseWidget::DrawState state) {
        switch(state) {
            case BaseWidget::DrawState::BW_DS_NONE: {
                return none;
            }
            case BaseWidget::DrawState::BW_DS_HOVERED: {
                return hovered;
            }
            case BaseWidget::DrawState::BW_DS_PRESSED: {
                return pressed;
            }
            case BaseWidget::DrawState::BW_DS_ACTIVATED: {
                return activated;
            }
            case BaseWidget::DrawState::BW_DS_DISABLED: {
                return disabled;
            }
            default: {
                return none;
            }
        }
    }
};

class FocusManager {
public:
    static FocusManager& instance();

    inline bool hasFocusedWidget() {
        return m_focused != nullptr;
    }

    inline bool isFocused(BaseWidget* widget) {
        return widget == m_focused;
    }

    // TODO: Focus gain / loss events?
    inline void focus(BaseWidget* widget) {
        m_focused = widget;
    }

    inline void clearFocus() {
        m_focused = nullptr;
    }

    bool delegateEventToFocusedWidget(sf::Event &event);
private:
    BaseWidget* m_focused{nullptr};
};

}}

#endif //GWIDI_SFML_BASEWIDGET_H
