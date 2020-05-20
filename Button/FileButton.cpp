
#include "FileButton.h"
FileButton::FileButton(float x, float y, float x_size, float y_size, sf::RenderWindow* window,
                       DrawingField* field):
        field_(field){
    window_ = window;

    button_.setFillColor(sf::Color::Blue);
    button_.setSize(sf::Vector2f(x_size, y_size));
    button_.setPosition(x, y);
    button_.setOutlineThickness(2);
    button_.setOutlineColor(sf::Color::Yellow);

    if (!font_.loadFromFile("arial.ttf")) {
        throw std::logic_error("Cannot load font in FileButton");
    }
    text_.setFont(font_);
    text_.setString("File");
    text_.setCharacterSize(17);
    text_.setFillColor(sf::Color::Yellow);
    text_.setPosition(x + x_size / 2 - text_.getLocalBounds().width / 2,
                      y + y_size / 2 - text_.getLocalBounds().height / 2 - 3);

}

void FileButton::ProcessEvent(const sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));
        std::cout<<mouse_coordinats.x<<" "<<mouse_coordinats.y<<std::endl;
        if (button_.getGlobalBounds().contains(mouse_coordinats)) {
            ProcessPress();
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        ProcessRelease();
    }
    if (menu_) {
        menu_->ProcessEvent(event);
    }
}

void FileButton::ProcessPress() {
    button_.setOutlineColor(sf::Color::Red);

    menu_ = new FileMenu(window_, button_.getPosition().x,
                         button_.getPosition().y + button_.getSize().y + 2,
                         sf::Vector2f(100, 100));
}

void FileButton::ProcessRelease() {
}

void FileButton::Process()  {
    if (menu_ && menu_->HasResult()) {
        switch (menu_->GetResult()) {
            case Save: {
                field_->Save();
            }
                break;
            case SaveAs: {
                std::string result;
                bool success = true;
                QuestionWindow ask_window("Save as...", result, 400, 100, success);
                ask_window.Await();
                if (success) field_->SaveAs(result);
            }
                break;
            case Load: {
                std::string result;
                bool success = true;
                QuestionWindow ask_window("Load", result, 400, 100, success);
                ask_window.Await();
                if (success) field_->Load(result);
            }
            case Empty: {

            }
        }
        delete menu_;
        menu_ = nullptr;
        button_.setOutlineColor(sf::Color::Yellow);
    }
}

void FileButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(button_, states);
    target.draw(text_, states);
    if (menu_) {
        target.draw(*menu_, states);
    }
}