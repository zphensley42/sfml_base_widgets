#include "TextWidget.h"
#include "FontManager.h"

namespace sfml { namespace base {

TextWidget::TextWidget() : TextWidget("") {}
TextWidget::TextWidget(const std::string& text) {
    m_label.setFont(FontManager::instance().buttonFont());
    setText(text);
};


void TextWidget::setText(const std::string &text, unsigned int size, sf::Color color) {
    m_label.setString(text);
    m_label.setCharacterSize(size);
    m_label.setFillColor(color);
}

std::string TextWidget::getText() {
    return m_label.getString();
}

void TextWidget::init() {
    m_background.setFillColor(sf::Color::Transparent);
    m_background.setSize({ m_bounds.width, m_bounds.height});

    reposition();
}

// TODO: This again seems inefficient due to allocations
// TODO: Just copy over button (with background) and do not bring any of the state stuff (global bounds is needed to give real coords)
// TODO: Inefficient, but w/e for now
void TextWidget::reposition() {
    m_background.setPosition({m_bounds.left, m_bounds.top});
    auto center = m_background.getPosition() + (m_background.getSize() / 2.f);
    auto labelLb = m_label.getLocalBounds();

    switch(m_textAlign) {
        case BaseWidget::ALIGN_LEFT: {
            m_label.setOrigin(0, labelLb.height / 2.f);
            m_label.setPosition(m_background.getPosition().x, center.y);
            break;
        }
        case BaseWidget::ALIGN_CENTER: {
            m_label.setOrigin({labelLb.width / 2.f, labelLb.height / 2.f});
            m_label.setPosition(center);
            break;
        }
        case BaseWidget::ALIGN_RIGHT: {
            m_label.setOrigin({labelLb.width, labelLb.height / 2.f});
            m_label.setPosition(m_background.getPosition().x - labelLb.width, center.y);
            break;
        }
    }
}

void TextWidget::draw(sf::View* v, sf::RenderWindow &w) {
    if(!m_drawn) {
        m_drawn = true;
        init();
    }

    if(v) {
        w.setView(*v);
    }

    reposition();
    w.draw(m_background);
    w.draw(m_label);
}

sf::FloatRect TextWidget::globalBounds() {
    return m_background.getGlobalBounds();
}

void TextWidget::onDrawStateChanged(DrawState oldState, DrawState newState) {

}

bool TextWidget::delegateEvent(sf::RenderWindow &window, sf::Event &event, sf::View *view) {
    return false;
}

void TextWidget::setSize(sf::Vector2f size) {
    BaseWidget::setSize(size);

    m_drawn = false;
    reposition();
}

void TextWidget::setPosition(sf::Vector2f position) {
    BaseWidget::setPosition(position);
    reposition();
}

void TextWidget::setTextAlign(TextAlign align) {
    m_textAlign = align;
    reposition();
}

}}
