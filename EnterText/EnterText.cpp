
#include "EnterText.h"
EnterText::EnterText(sf::RenderWindow *window, float x, float y, float len) {
    window_ = window;
    if (!font_.loadFromFile("arial.ttf")) {
        throw std::logic_error("Cannot load font in EnterText");
    }
    line_.setPosition(x, y);
    line_.setSize(sf::Vector2f(len, 40));
    line_.setFillColor(sf::Color::Blue);
    line_.setOutlineColor(sf::Color::Yellow);
    line_.setOutlineThickness(3);

    text_.setFont(font_);
    text_.setCharacterSize(20);
    text_.setPosition(x + 3, y + line_.getSize().y / 2 - text_.getLocalBounds().height / 2 - 10);
    text_.setFillColor(sf::Color::White);
}

bool EnterText::IsActive() const {
    return is_active_;
}

sf::FloatRect EnterText::getLocalBounds() {
    return line_.getLocalBounds();
}

void EnterText::ProcessEvent(const sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));
        SetActive(line_.getGlobalBounds().contains(mouse_coordinats));
    }
    if (event.type == sf::Event::TextEntered && IsActive()) {
        ProcessChar(event.text.unicode);
    }
}
bool EnterText::GetEnding() const {
    return has_ending_;
}
void EnterText::SetEnding(bool ending) {
    if (ending && !has_ending_) {
        entered_text_.push_back(ending_);
    }
    if (!ending && has_ending_) {
        entered_text_.pop_back();
    }
    has_ending_ = ending;
    text_.setString(entered_text_);
}
void EnterText::SetActive(bool active) {
    if (is_active_ && !active) {
        line_.setOutlineColor(sf::Color::Yellow);
        SetEnding(false);
    }
    if (!is_active_ && active) {
        line_.setOutlineColor(sf::Color::Red);
    }
    is_active_ = active;
}
void EnterText::Process() {
    if (IsActive()) {
        int current_time = timer.getElapsedTime().asMilliseconds();
        SetEnding((current_time / 300) % 2 == 0);
    }
}
bool EnterText::IsEntered() const {
    return entered_;
}
std::string EnterText::GetEntered() const {
    return entered_text_;
}
bool EnterText::ProcessChar(int input) {
    if (entered_)
        return false;
    else if (input == '\r') {
        entered_ = true;
        return true;
    }
    else {
        if (GetEnding()) {
            entered_text_.pop_back();
        }
        if (input == '\b') {
            if (!entered_text_.empty())
                entered_text_.pop_back();
        }
        else {
            if (line_.getGlobalBounds().width < text_.getGlobalBounds().width + 36) {
                if (GetEnding()) {
                    entered_text_.push_back(ending_);
                }
                return false;
            }
            entered_text_.push_back(input);
        }
        if (GetEnding()) {
            entered_text_.push_back(ending_);
        }
        text_.setString(entered_text_);
        return true;
    }
}

void EnterText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(line_, states);
    target.draw(text_, states);
}