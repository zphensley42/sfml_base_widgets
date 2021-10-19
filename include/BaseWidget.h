#ifndef GWIDI_SFML_BASEWIDGET_H
#define GWIDI_SFML_BASEWIDGET_H

#include <SFML/Graphics.hpp>

namespace sfml { namespace base {

class BaseWidget {
public:
    enum TextAlign {
        ALIGN_LEFT = 0,
        ALIGN_CENTER,
        ALIGN_RIGHT,
    };

    enum DrawState {
        BW_DS_NONE = 0,
        BW_DS_HOVERED,
        BW_DS_PRESSED,
        BW_DS_ACTIVATED,
        BW_DS_DISABLED,
    };
    BaseWidget() = default;
    virtual ~BaseWidget() = default;

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    virtual bool delegateEvent(sf::RenderWindow& window, sf::Event &event);

    virtual void onDrawStateChanged(DrawState oldState, DrawState newState) {}

    virtual sf::FloatRect globalBounds();

    void addChild(BaseWidget* child);

    virtual void draw(sf::View* v, sf::RenderWindow &w) {}
protected:
    DrawState m_drawState{BW_DS_NONE};
    sf::FloatRect m_bounds;
    BaseWidget* m_parent;
    std::vector<BaseWidget*> m_children;

    bool m_drawn{false};

private:
    void determineState(bool hovered, bool pressed, bool activated, bool disabled);
    void updateState(DrawState state);
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

    inline bool hasPressedWidget() {
        return m_pressed != nullptr;
    }

    inline bool hasHoveredWidget() {
        return m_hovered != nullptr;
    }

    inline bool isPressed(BaseWidget* widget) {
        return widget == m_pressed;
    }

    inline bool isHovered(BaseWidget* widget) {
        return widget == m_hovered;
    }

    // TODO: Focus gain / loss events?
    inline void press(BaseWidget* widget) {
        m_pressed = widget;
    }

    inline void hover(BaseWidget* widget) {
        m_hovered = widget;
    }

    inline void clearPressed() {
        m_pressed = nullptr;
    }

    inline void clearHovered() {
        m_hovered = nullptr;
    }

    bool delegateEventToNecessaryWidgets(sf::Event &event);
private:
    BaseWidget* m_pressed{nullptr};
    BaseWidget* m_hovered{nullptr};
};

}}

#endif //GWIDI_SFML_BASEWIDGET_H
