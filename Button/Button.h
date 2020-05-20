#ifndef EDITOR_BUTTON_H
#define EDITOR_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "../Menu/Menu.h"
#include "../InteractionWindows/QuestionWindow.h"

class Button: public sf::Drawable, public sf::Transformable {
public:
    virtual void ProcessEvent(const sf::Event event) = 0;
    bool GetState() const {
        return is_pressed_;
    }
    bool ExtractState() {
        bool state = is_pressed_;
        is_pressed_ = false;
        return state;
    }
    void SetState(bool state) {
        is_pressed_ = state;
    }
    virtual void ProcessPress() = 0;
    virtual void ProcessRelease() = 0;
    virtual void Process() = 0;
protected:
    sf::RectangleShape button_;
    bool is_pressed_ = false;
    sf::RenderWindow* window_ = nullptr;
};
#endif //EDITOR_BUTTON_H
