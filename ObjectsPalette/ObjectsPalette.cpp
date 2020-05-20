#include "ObjectsPalette.h"

ObjectsPalette::ObjectsPalette(float x, float y, float x_size, float y_size, sf::RenderWindow* window):
        window_(window) {
    if (!global_texture_.loadFromFile("sprites.png")) {
        throw std::logic_error("cannot load sprites from file");
    }
    textures_.resize(buttons_count);
    for (int i = 0; i < buttons_count; ++i) {
        if (!textures_[i].loadFromFile("sprites.png",
                                       sf::IntRect(52, 17 + i * 83, 74, 74))) {
            throw std::logic_error("cannot load sprites from file");
        }
    }
    names_.resize(buttons_count);
    names_[0] = "flame";
    names_[1] = "coin";
    names_[2] = "block";
    names_[3] = "stone";
    for (int i = 0; i < buttons_count; ++i) {
        buttons_.emplace_back(x, y + y_size / buttons_count * i,
                              x_size, y_size / buttons_count,
                              &(textures_[i]), buttons_,
                              this,
                              window_);
    }
    buttons_[0].ProcessPress();
}

void ObjectsPalette::ProcessEvent(const sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < buttons_count; ++i) {
            std::cout<<"Test"<<std::endl;
            buttons_[i].ProcessEvent(event);
        }
    }
}

TextureInfo ObjectsPalette::getChosenTexture() {
    for (int i = 0; i < buttons_count; ++i) {
        if (buttons_[i].GetState()) {
            std::cout<<"i"<<" "<<names_[i]<<std::endl;
            return {&textures_[i], &names_[i],
                    sf::IntRect(52, 17 + i * 83, 74, 74)};
        }
    }
    return {nullptr, nullptr, sf::IntRect()};
}

TextureInfo ObjectsPalette::getTexture(const std::string& name) {
    for (int i = 0; i < buttons_count; ++i) {
        if (names_[i] == name) {
            return {&textures_[i], &names_[i],
                    sf::IntRect(52, 17 + i * 83, 74, 74)};
        }
    }
    return {nullptr, nullptr, sf::IntRect()};
}
sf::Texture* ObjectsPalette::getGlobalTexture() {
    return &global_texture_;
}

void ObjectsPalette::draw(sf::RenderTarget& target, sf::RenderStates states) const {
states.transform *= getTransform();
for (int i = 0; i < buttons_count; ++i)
target.draw(buttons_[i], states);
}