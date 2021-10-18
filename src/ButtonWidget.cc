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

float ButtonWidget::getHeight() {
    return m_bounds.height;
}

void ButtonWidget::setForegroundColors(DrawStateColorMapping foreground) {
    m_stateForegroundColors = foreground;
}
void ButtonWidget::setBackgroundColors(DrawStateColorMapping background) {
    m_stateBackgroundColors = background;
}

void ButtonWidget::setText(const std::string &text) {
    m_label.setString(text);
    m_label.setCharacterSize(16);
}

void ButtonWidget::init() {
    m_label.setFont(FontManager::instance().buttonFont());
    m_background.setSize({ m_bounds.width, m_bounds.height});

    reposition();
}

// TODO: This again seems inefficient due to allocations
void ButtonWidget::reposition() {
    m_background.setPosition({m_bounds.left, m_bounds.top});

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

    reposition();

    w.draw(m_background);
    w.draw(m_label);
}

void ButtonWidget::onDrawStateChanged(DrawState oldState, DrawState newState) {
    // Determine if we were 'clicked' (i.e. pressed and released within the bounds)
    if(oldState == DrawState::BW_DS_PRESSED && newState == DrawState::BW_DS_HOVERED) {
        if(m_listener) {
            m_listener();
        }
    }
}

bool ButtonWidget::delegateEvent(sf::RenderWindow& window, sf::Event &event) {
    return BaseWidget::delegateEvent(window, event);   // Nothing to add currently
}

void ButtonWidget::setClickedListener(std::function<void()> listener) {
    m_listener = listener;
}

sf::FloatRect ButtonWidget::globalBounds() {
    return m_background.getGlobalBounds();
}

}}