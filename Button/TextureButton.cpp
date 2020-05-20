
#include "TextureButton.h"
TextureButton::TextureButton(float x, float y, float x_size, float y_size,
                             sf::Texture* texture,
                             std::vector<TextureButton>& buttons,
                             ObjectsPalette* parent,
                             sf::RenderWindow* window):
        texture_(texture),
        buttons_(buttons),
        parent_(parent) {
    window_ = window;
    button_.setSize(sf::Vector2f(x_size - 2 * border_size_,
                                 y_size - 2 * border_size_));
    button_.setPosition(x, y);
    button_.setOutlineThickness(border_size_);
    button_.setOutlineColor(sf::Color::Yellow);
    button_.setTexture(texture);
}

void TextureButton::ProcessEvent(const sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));
        std::cout<<mouse_coordinats.x<<" "<<mouse_coordinats.y<<std::endl;
        if (button_.getGlobalBounds().contains(mouse_coordinats)) {
            ProcessPress();
        }
    }
}

void TextureButton::ProcessPress() {
    for (int i = 0; i < buttons_.size(); ++i) {
        buttons_[i].ProcessRelease();
    }
    button_.setOutlineColor(sf::Color::Red);
    is_pressed_ = true;
}

void TextureButton::ProcessRelease() {
    button_.setOutlineColor(sf::Color::Yellow);
    is_pressed_ = false;
}

void TextureButton::Process() {

}

void TextureButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(button_, states);
}