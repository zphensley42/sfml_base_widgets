#include "ButtonWidget.h"
#include "FontManager.h"

namespace sfml { namespace base {

ButtonWidget::ButtonWidget() : ButtonWidget("") {}
ButtonWidget::ButtonWidget(const std::string &text) : BaseWidget() {
    m_label.setString(text);
}
ButtonWidget::ButtonWidget(const std::string &text, DrawStateColorMapping background, DrawStateColorMapping foreground) : BaseWidget(),
                                                                                                   m_stateForegroundColors{foreground},
                                                                                                   m_stateBackgroundColors{background} {
    m_label.setString(text);
    m_label.setCharacterSize(16);
}

void ButtonWidget::init() {
    m_background.setSize({ m_bounds.width, m_bounds.height});
    m_background.setPosition({m_bounds.left, m_bounds.top});

    m_label.setFont(FontManager::instance().buttonFont());
    auto center = m_background.getPosition() + (m_background.getSize() / 2.f);

    auto labelLb = m_label.getLocalBounds();
    m_label.setOrigin({labelLb.width / 2.f, labelLb.height / 2.f});
    m_label.setPosition(center);
}

void ButtonWidget::draw(sf::View* v, sf::RenderWindow &w) {
    if(!m_drawn) {
        m_drawn = true;
        init();
    }

    if(v) {
        w.setView(*v);
    }
    // Assign appropriate colors
    m_background.setFillColor(m_stateBackgroundColors.forState(m_drawState));
    m_label.setFillColor(m_stateForegroundColors.forState(m_drawState));
    w.draw(m_background);
    w.draw(m_label);
}

void ButtonWidget::delegateEvent(sf::Event &event) {
    switch(event.type) {
        case sf::Event::EventType::MouseButtonPressed: {
            if(m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                FocusManager::instance().focus(this);
                m_drawState = DrawState::BW_DS_PRESSED;
            }
            break;
        }
        case sf::Event::EventType::MouseButtonReleased: {
            if(FocusManager::instance().isFocused(this)) {
                FocusManager::instance().clearFocus();

                auto inBounds = m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
                // TODO: Take into account activated / disabled states instead of defaulting to NONE
                m_drawState = inBounds ? DrawState::BW_DS_HOVERED : DrawState::BW_DS_NONE;

                // If we are in bounds when we release, this was a full click
                if(inBounds && m_listener) {
                    m_listener();
                }
            }
            break;
        }
        case sf::Event::EventType::MouseMoved: {
            auto hasFocus = FocusManager::instance().hasFocusedWidget();
            auto isFocused = FocusManager::instance().isFocused(this);

            // If we have focus but this isn't the focused widget, do nothing
            // If we have focus and are focused, we are in down state
            // If we do not have focus, move to hover logic
            // TODO: Take into account activated / disabled states instead of defaulting to NONE

            if(hasFocus && isFocused) {
                m_drawState = DrawState::BW_DS_PRESSED;
            }
            else if(hasFocus) {
                m_drawState = DrawState::BW_DS_NONE;
            }
            else {
                auto inBounds = m_background.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);
                m_drawState = inBounds ? DrawState::BW_DS_HOVERED : DrawState::BW_DS_NONE;
            }
            break;
        }
    }
    // TODO: Fill-in
}

void ButtonWidget::setClickedListener(std::function<void()> listener) {
    m_listener = listener;
}

}}