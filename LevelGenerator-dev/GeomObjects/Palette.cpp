#include "Palette.h"

Palette::Palette(sf::Vector2f pos, sf::Vector2f sizes, TextureManager *tex_manager, EventManager *click_manager,
                 sf::RenderWindow *window_ptr, const std::vector<TextureName> &landscapes) :
        pos_(pos),
        size_(sizes),
        landscape_cnt_(landscapes.size() + 1),
        tex_manager_(tex_manager),
        click_manager_(click_manager),
        window_ptr_(window_ptr) {

    if (!font_.loadFromFile("arial.ttf")) {
        throw std::runtime_error("It is not possible to load the font");
    }
    setName("Color Palette");

    sf::FloatRect button_size = static_cast<sf::FloatRect>(tex_manager_->getRect(TextureName::Grass));
    float shift = (size_.x - button_size.width * landscape_cnt_) / (static_cast<float>(landscape_cnt_) + 1);
    for (size_t i = 0; i < landscapes.size(); ++i) {
        sf::Vector2f button_pos = {pos_.x + (shift + button_size.width) * i + shift, pos_.y + size_.y / 2};
        landscape_buttons_.emplace_back(button_pos, sf::Vector2f(button_size.width, button_size.height),
                                        tex_manager_, landscapes[i]);
    }
    sf::Vector2f button_pos = {pos_.x + (shift + button_size.width) * landscapes.size() + shift, pos_.y + size_.y / 2};
    landscape_buttons_.emplace_back(button_pos, sf::Vector2f(button_size.width, button_size.height),
                                    tex_manager_, TextureName::Emptiness);

    for (auto& button : landscape_buttons_) {
        click_manager_->addWindowObj(&button, window_ptr_);
    }
}

void Palette::setName(std::string &&name) {
    name_.setString("Color Palette");
    name_.setFont(font_);
    name_.setFillColor(sf::Color::Black);
    name_.setCharacterSize(25);
    name_.setStyle(sf::Text::Italic);
    alignName();
    fontSizeNormalize();
}

void Palette::alignName() {
    sf::FloatRect rect = name_.getGlobalBounds();
    sf::Vector2f rect_centre = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
    name_.setOrigin(rect_centre);
    sf::Vector2f button_centre = pos_ + sf::Vector2f(size_.x / 2, size_.y / 6);
    name_.setPosition(button_centre);
}

void Palette::fontSizeNormalize() {
    float scale_aspect_x = 0.8f * (size_.x / name_.getLocalBounds().width);
    float scale_aspect_y = 0.9f * ((size_.y / 5) / name_.getLocalBounds().height);
    float scale_aspect = std::min(1.f, std::min(scale_aspect_x, scale_aspect_y));
    name_.setScale(scale_aspect, scale_aspect);
}

void Palette::drawBackground(sf::RenderTarget &target) const {
    sf::RectangleShape background(size_);
    background.setPosition(pos_);
    background.setFillColor(sf::Color(255, 250, 205));
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::Black);
    target.draw(background);
}

void Palette::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawBackground(target);
    target.draw(name_);
    for (const LandscapeButton& landscape_button: landscape_buttons_) {
        target.draw(landscape_button, states);
    }
}
