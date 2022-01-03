#include <iostream>
#include "BaseWidget.h"

namespace sfml { namespace base {

BaseWidget::~BaseWidget() {
    clearChildren();
}

void BaseWidget::addChild(BaseWidget *child) {
    m_children.push_back(child);
    child->m_parent = this;
}

void BaseWidget::clearChildren() {
    for(auto& child : m_children) {
        child->m_parent = nullptr;
        delete child;
    }
    m_children.clear();
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

bool BaseWidget::delegateEvent(sf::RenderWindow& window, sf::Event &event, sf::View* view) {
    auto p = sf::Mouse::getPosition(window);
    auto mousePos = window.mapPixelToCoords({p.x, p.y}, view ? *view : window.getView());
    auto gb = globalBounds();

    switch(event.type) {
        case sf::Event::EventType::MouseButtonPressed: {
            // Left click for focus states
            if(event.mouseButton.button == 0) {
                if(gb.contains(mousePos.x, mousePos.y)) {

                    FocusManager::instance().press(this);

                    determineState(
                            FocusManager::instance().isHovered(this),
                            FocusManager::instance().isPressed(this),
                            m_activated,
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
                            m_activated,
                            false
                    );
                }
            }
            break;
        }
        case sf::Event::EventType::MouseMoved: {
            auto inBounds = gb.contains(mousePos.x, mousePos.y);
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
                    m_activated,
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

void BaseWidget::setActivated(bool activated) {
    m_activated = activated;
    determineState(
            FocusManager::instance().isHovered(this),
            FocusManager::instance().isPressed(this),
            m_activated,
            false
    );
}

bool BaseWidget::isActivated() {
    return m_activated;
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