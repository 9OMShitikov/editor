
#ifndef EDITOR_QUESTIONWINDOW_H
#define EDITOR_QUESTIONWINDOW_H
#include "SFML/Graphics.hpp"
#include "../EnterText/EnterText.h"

class QuestionWindow: public sf::RenderWindow {
public:
    explicit QuestionWindow(const std::string& question, std::string& answer,
            float width, float height, bool& success):
            success_(success),
            box_(this, 1, height / 2, width - 2),
            answer_(answer),
            sf::RenderWindow(sf::VideoMode(width, height), "Queston window") {
        if (!font_.loadFromFile("arial.ttf")) {
            throw std::logic_error("cannot load font in question window");
        }
        text_.setFont(font_);
        text_.setString(question);
        text_.setFillColor(sf::Color::Blue);
        text_.setCharacterSize(15);
        text_.setPosition(width / 2 - text_.getLocalBounds().width / 2,
                          height / 4 - text_.getLocalBounds().height / 2);
    }

    void Await() {
        success_ = false;
        while(isOpen()) {
            sf::Event event;
            while (pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    close();
                    break;
                } else {
                    box_.ProcessEvent(event);
                }
            }

            box_.Process();

            if (box_.IsEntered()) {
                answer_ = box_.GetEntered();
                success_ = true;
                close();
            }
            clear(sf::Color::Cyan);
            draw(box_);
            draw(text_);
            display();
        }
    }
private:
    std::string& answer_;
    sf::Text text_;
    sf::Font font_;
    EnterText box_;
    bool& success_;
};


#endif //EDITOR_QUESTIONWINDOW_H
