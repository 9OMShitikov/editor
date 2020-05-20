#ifndef LEVELGENERATOR_WINDOWOBJ_H
#define LEVELGENERATOR_WINDOWOBJ_H

#include <SFML/Graphics.hpp>
#include <iostream>

class WindowObj : public sf::Drawable, public sf::Transformable {
public:
    virtual sf::Vector2f getSize() const = 0;
    virtual void setSize(const sf::Vector2f&) {};

    virtual void AcceptEvent(sf::Event&, const sf::Vector2f &pos) = 0;
};

#endif //LEVELGENERATOR_WINDOWOBJ_H
