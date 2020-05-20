#ifndef EDITOR_OBJECTSPALETTE_H
#define EDITOR_OBJECTSPALETTE_H
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include <vector>
#include <string>

class ObjectsPalette;

class TextureButton: public Button {
public:
    TextureButton(float x, float y, float x_size, float y_size,
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

    void ProcessEvent(const sf::Event event) override{
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));
            std::cout<<mouse_coordinats.x<<" "<<mouse_coordinats.y<<std::endl;
            if (button_.getGlobalBounds().contains(mouse_coordinats)) {
                ProcessPress();
            }
        }
    }

    void ProcessPress() override {
        for (int i = 0; i < buttons_.size(); ++i) {
            buttons_[i].ProcessRelease();
        }
        button_.setOutlineColor(sf::Color::Red);
        is_pressed_ = true;
    }

    void ProcessRelease() override {
        button_.setOutlineColor(sf::Color::Yellow);
        is_pressed_ = false;
    }

    void Process() override {

    }
private:
    float border_size_ = 4;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(button_, states);
    }

    ObjectsPalette* parent_ = nullptr;
    std::vector<TextureButton>& buttons_;
    sf::Texture* texture_;
};

struct TextureInfo {
    sf::Texture* texture = nullptr;
    std::string* name = nullptr;
    sf::IntRect borders;
};

class ObjectsPalette: public sf::Drawable, sf::Transformable {
public:
    ObjectsPalette(float x, float y, float x_size, float y_size, sf::RenderWindow* window):
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

    void ProcessEvent(const sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (int i = 0; i < buttons_count; ++i) {
                std::cout<<"Test"<<std::endl;
                buttons_[i].ProcessEvent(event);
            }
        }
    }

    TextureInfo getChosenTexture() {
        for (int i = 0; i < buttons_count; ++i) {
            if (buttons_[i].GetState()) {
                std::cout<<"i"<<" "<<names_[i]<<std::endl;
                return {&textures_[i], &names_[i],
                        sf::IntRect(52, 17 + i * 83, 74, 74)};
            }
        }
        return {nullptr, nullptr, sf::IntRect()};
    }

    TextureInfo getTexture(const std::string& name) {
        for (int i = 0; i < buttons_count; ++i) {
            if (names_[i] == name) {
                return {&textures_[i], &names_[i],
                        sf::IntRect(52, 17 + i * 83, 74, 74)};
            }
        }
        return {nullptr, nullptr, sf::IntRect()};
    }
    sf::Texture* getGlobalTexture() {
        return &global_texture_;
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        for (int i = 0; i < buttons_count; ++i)
            target.draw(buttons_[i], states);
    }

    size_t buttons_count = 4;
    sf::RenderWindow* window_;
    sf::Texture global_texture_;
    std::vector <sf::Texture> textures_;
    std::vector <std::string> names_;
    std::vector <TextureButton> buttons_;
};


#endif //EDITOR_OBJECTSPALETTE_H
