#include "FontManager.h"

namespace sfml { namespace base {

FontManager& FontManager::instance() {
    static FontManager s;
    return s;
}

FontManager::FontManager() {
    m_buttonFont.loadFromFile("E:/tools/repos/gwidi_sfml/assets/arial.ttf");
}

}}