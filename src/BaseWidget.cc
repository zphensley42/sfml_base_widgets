#include <iostream>
#include "BaseWidget.h"

namespace sfml { namespace base {

void BaseWidget::addChild(BaseWidget *child) {
    m_children.push_back(child);
    child->m_parent = this;
}

void BaseWidget::setSize(sf::Vector2f size) {
    m_bounds.width = size.x;
    m_bounds.height = size.y;
}

void BaseWidget::setPosition(sf::Vector2f position) {
    m_bounds.left = position.x;
    m_bounds.top = position.y;
}

sf::FloatRect BaseWidget::globalBounds() {
    return m_bounds;
}

void BaseWidget::updateState(BaseWidget::DrawState state) {
    auto oldState = m_drawState;
    m_drawState = state;
    onDrawStateChanged(oldState, state);
}

bool BaseWidget::delegateEvent(sf::RenderWindow& window, sf::Event &event) {
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

                    return true;
                }
            }
            break;
        }
        case sf::Event::EventType::MouseButtonReleased: {
            // Left click for focus states
            if(event.mouseButton.button == 0) {
                if(FocusManager::instance().isPressed(this)) {
                    FocusManager::instance().clearPressed();

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
            auto mPos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            auto gB = globalBounds();
            auto inBounds = gB.contains(mPos.x, mPos.y);
            if(inBounds) {
                FocusManager::instance().hover(this);
            }
            else {
                if(FocusManager::instance().isHovered(this)) {
                    FocusManager::instance().clearHovered();
                }
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

    return false;
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
//    if(hasPressedWidget()) {
//        if(m_pressed->delegateEvent(event)) {
//            return true;
//        }
//    }
//
//    if(hasHoveredWidget()) {
//        if(m_hovered->delegateEvent(event)) {
//            return true;
//        }
//    }
    return false;
}

}}