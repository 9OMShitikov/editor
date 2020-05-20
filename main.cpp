#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button/FileButton.h"
#include "ObjectsPalette/ObjectsPalette.h"
#include "DrawingField/DrawingField.h"
#include <math.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Editor");
    ObjectsPalette icon(600, 300, 50, 50 * 4, &window);

    DrawingField field (&window, &icon, 10, 10, 50, 50, 500, 500);

    FileButton button (600, 50, 100, 50, &window, &field);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
            }
            else {
                button.ProcessEvent(event);
                icon.ProcessEvent(event);
                field.ProcessEvent(event);
            }
        }

        button.Process();

        window.clear();
        window.draw(button);
        window.draw(icon);
        window.draw(field);
        window.display();
    }

    return 0;
}