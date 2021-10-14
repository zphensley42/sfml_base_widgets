#include "BaseWidget.h"
#include "ButtonWidget.h"
#include <vector>
#include <iostream>


int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    std::vector<sfml::base::BaseWidget*> widgets;
    auto button = new sfml::base::ButtonWidget("Test Button",
                                               {
                                                       sf::Color::White,
                                                       sf::Color::Blue,
                                                       sf::Color::Red,
                                                       sf::Color::Green,
                                                       sf::Color(50, 50, 50, 255)
                                               },
                                               {
                                                       sf::Color::Black,
                                                       sf::Color::Black,
                                                       sf::Color::Black,
                                                       sf::Color::Black,
                                                       sf::Color::Black,
                                               });
    widgets.push_back(button);
    button->setSize({100, 50});
    button->setPosition({10, 10});
    button->setClickedListener([](){
        std::cout << "Button clicked\n";
    });


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            else {
                // Delegate (Focused widget first, other widgets if none)
                if(!sfml::base::FocusManager::instance().delegateEventToNecessaryWidgets(event)) {
                    for(auto& widget : widgets) {
                        widget->delegateEvent(event);
                    }
                }
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw our UI
        for(auto& widget: widgets) {
            widget->draw(nullptr, window);
        }

        // Update the window
        window.display();
    }

    for(auto& widget : widgets) {
        delete widget;
    }
    widgets.clear();

    return EXIT_SUCCESS;
}