#ifndef SFML_BASE_WIDGETS_FONTMANAGER_H
#define SFML_BASE_WIDGETS_FONTMANAGER_H

#include <SFML/Graphics.hpp>

namespace sfml { namespace base {

class FontManager {
public:
    static FontManager& instance();

    FontManager();

    inline sf::Font& buttonFont() {
        return m_buttonFont;
    }
private:
    sf::Font m_buttonFont;
};

}}


#endif //SFML_BASE_WIDGETS_FONTMANAGER_H
