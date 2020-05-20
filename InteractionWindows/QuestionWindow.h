
#ifndef EDITOR_QUESTIONWINDOW_H
#define EDITOR_QUESTIONWINDOW_H
#include "SFML/Graphics.hpp"
#include "../EnterText/EnterText.h"

class QuestionWindow: public sf::RenderWindow {
public:
    explicit QuestionWindow(const std::string& question, std::string& answer,
            float width, float height, bool& success);

    void Await();
private:
    std::string& answer_;
    sf::Text text_;
    sf::Font font_;
    EnterText box_;
    bool& success_;
};


#endif //EDITOR_QUESTIONWINDOW_H
