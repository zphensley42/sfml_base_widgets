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

sf::FloatRect& BaseWidget::globalBounds() {
    return m_bounds;
}

void BaseWidget::updateState(BaseWidget::DrawState state) {
    auto oldState = m_drawState;
    m_drawState = state;
    onDrawStateChanged(oldState, state);
}

void BaseWidget::delegateEvent(sf::Event &event) {
    switch(event.type) {
        case sf::Event::EventType::MouseButtonPressed: {
            // Left click for focus states
            if(event.mouseButton.button == 0) {
                if(globalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    FocusManager::instance().press(this);

                    determineState(
                            FocusManager::instance().isHovered(this),
                            FocusManager::instance().isPressed(this),
                            false,
                            false
                    );
                }
            }
            break;
        }
        case sf::Event::EventType::MouseButtonReleased: {
            // Left click for focus states
            if(event.mouseButton.button == 0) {
                if(FocusManager::instance().isPressed(this)) {
                    FocusManager::instance().clearPressed();

                    auto inBounds = globalBounds().contains(event.mouseButton.x, event.mouseButton.y);

                    determineState(
                            FocusManager::instance().isHovered(this),
                            FocusManager::instance().isPressed(this),
                            false,
                            false
                    );
                }
            }
            break;
        }
        case sf::Event::EventType::MouseMoved: {
            auto inBounds = globalBounds().contains(event.mouseMove.x, event.mouseMove.y);
            if(inBounds) {
                FocusManager::instance().hover(this);
            }
            else {
                if(FocusManager::instance().isHovered(this)) {}
                FocusManager::instance().clearHovered();
            }

            determineState(
                    FocusManager::instance().isHovered(this),
                    FocusManager::instance().isPressed(this),
                    false,
                    false
                    );
            break;
        }
    }
}

void BaseWidget::determineState(bool hovered, bool pressed, bool activated, bool disabled) {
    if(disabled) {
        updateState(DrawState::BW_DS_DISABLED);
    }
    else {
        if(pressed) {
            updateState(DrawState::BW_DS_PRESSED);
        }
        else {
            updateState(hovered ? DrawState::BW_DS_HOVERED : (activated ? DrawState::BW_DS_ACTIVATED : BW_DS_NONE));
        }
    }
}

FocusManager& FocusManager::instance() {
    static FocusManager s;
    return s;
}

bool FocusManager::delegateEventToNecessaryWidgets(sf::Event &event) {
    bool ret {false};
    if(hasPressedWidget()) {
        m_pressed->delegateEvent(event);
        ret = true;
    }

    if(hasHoveredWidget()) {
        m_hovered->delegateEvent(event);
        ret = true;
    }
    return false;
}

}}