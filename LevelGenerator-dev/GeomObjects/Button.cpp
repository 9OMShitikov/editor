#include "Button.h"
#include "../Managers/MouseStatus.h"
#include "../WindowObjects/DialogWindow.h"
#include "../WindowObjects/NotificationWindow.h"
#include <fstream>

Button::Button(sf::Vector2f pos, sf::Vector2f sizes, TextureManager* manager, TextureName texture, const sf::Color& color) :
    pos_(pos),
    size_(sizes),
    texture_name_(texture),
    manager_(manager) {

        if (!font_.loadFromFile("arial.ttf")) {
            throw std::runtime_error("It is not possible to load the font");
        }
        nameConstructor();
        spriteConstructor();

        if (texture != TextureName::Emptiness) {
            setTexture(texture);
        } else {
            setDefaultTexture(color);
        }
}

void Button::nameConstructor() {
    name_.setFont(font_);
    name_.setFillColor(sf::Color::Black);
    name_.setCharacterSize(25);
    name_.setStyle(sf::Text::Italic);
}

void Button::spriteConstructor() {
    sprite_.setSize(size_);
    sprite_.setPosition(pos_);
    sprite_.setOutlineThickness(1);
    sprite_.setOutlineColor(sf::Color::Black);
}

sf::Vector2f Button::getPos() const {
    return pos_;
}

void Button::setSize(const sf::Vector2f& size) {
    size_ = size;
    sprite_.setSize(size_);
    alignName();
    fontSizeNormalize();
}

sf::Vector2f Button::getSize() const {
    return size_;
}

sf::FloatRect Button::getLocalBounds() const {
    return sf::FloatRect(getPos(), getSize());
}

TextureName Button::getTextureName() const {
    return texture_name_;
}

void Button::setName(const std::string &name) {
    name_.setString(name);
    alignName();
    fontSizeNormalize();
}

void Button::setDefaultTexture(sf::Color color) {
    sprite_.setFillColor(color);
}

void Button::setTexture(TextureName texture) {
    sprite_.setTexture(manager_->getTexture(texture), false);
}

void Button::alignName() {
    sf::FloatRect rect = name_.getGlobalBounds();
    sf::Vector2f rect_centre = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
    name_.setOrigin(rect_centre);
    sf::Vector2f button_centre = sprite_.getPosition() +
                                 sf::Vector2f(sprite_.getSize().x / 2, sprite_.getSize().y / 2);
    name_.setPosition(button_centre);
}

void Button::fontSizeNormalize() {
    float scale_aspect_x = 0.9f * (size_.x / name_.getLocalBounds().width);
    float scale_aspect_y = 0.8f * (size_.y / name_.getLocalBounds().height);
    float scale_aspect = std::min(1.f, std::min(scale_aspect_x, scale_aspect_y));
    name_.setScale(scale_aspect, scale_aspect);
}

void Button::AcceptEvent(sf::Event &event, const sf::Vector2f& pos) {
    if (event.type == sf::Event::MouseButtonPressed && getLocalBounds().contains(pos)) {
        click();
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = manager_->getAllTextures();
    target.draw(sprite_, states);
    if (name_.getString() != "") {
        target.draw(name_, states);
    }
}

///////////////////////////////////////////////////

void LandscapeButton::setStatus(ButtonStatus new_status_) {
    sf::Color new_color = sprite_.getFillColor();
    status_ = new_status_;
    if (status_ == ButtonStatus::Activated) {
        new_color.a = 255;
        sprite_.setFillColor(new_color);
    } else {
        new_color.a = 150;
        sprite_.setFillColor(new_color);
    }
}

void LandscapeButton::click() {
    if (status_ == ButtonStatus::Deactivated) {
        setStatus(ButtonStatus::Activated);
        MouseStatus::setLandscapeButton(this);
    } else {
        setStatus(ButtonStatus::Deactivated);
        MouseStatus::setLandscapeButton(nullptr);
    }
}

void SaveButton::click() {
    std::string file_name;
    file_name.reserve(100);
    DialogWindow ask_window("What do you want to name this map?", &file_name, nullptr);
    ask_window.run();
    write_map(std::move(file_name));
}

void OpenButton::click() {
    std::string file_name;
    file_name.reserve(100);
    DialogWindow ask_window("What file do you want to open?", &file_name, nullptr);
    ask_window.run();
    read_map(std::move(file_name));
}

void ClearButton::click() {
    map_->clear();
}

///////////////////////////////////////////////////

void SaveButton::write_map(std::string &&file_name) const {
    if (file_name.size() < 6 || file_name.substr(file_name.size() - 5, 5) != ".yaml") {
        NotificationWindow popup_window("Expected yaml file format");
        popup_window.run();
        return;
    }

    std::ofstream file_out(file_name);

    for (int i = 0; i < manager_->getTextureCnt(); ++i) {
        auto tex_name = static_cast<TextureName>(i);
        file_out << YAML::Node(LandscapeObject(tex_name, manager_->getTextureFile(), manager_->getRect(tex_name)));
        if (i != manager_->getTextureCnt() - 1) {
            file_out << "\n---\n";
        }
    }
    file_out << "\n...\n";

    file_out << YAML::Node(SchematicMap(map_->getSizeInTiles().x, map_->getSizeInTiles().y, map_->getInfo()));
    file_out << "\n...";
    file_out.close();
}

void OpenButton::read_error(std::string &&error_description) {
    NotificationWindow popup_window(std::move(error_description));
    popup_window.run();
}

void OpenButton::read_map(std::string &&file_name) const {
    sf::Vector2u map_size;
    if (file_name.empty()) {
        return;
    } else if (file_name.size() < 6 || file_name.substr(file_name.size() - 5, 5) != ".yaml") {
        NotificationWindow popup_window("Expected yaml file format");
        popup_window.run();
        return;
    }

    std::vector<YAML::Node> info_blocks = YAML::LoadAllFromFile(file_name);
    auto map = info_blocks.back().as<SchematicMap>();
    if (map_->getSizeInTiles() != sf::Vector2u(map.width, map.height)) {
        read_error("Mismatch in map sizes");
        return;
    } else {
        map_->loadInfo(std::move(map.tiles));
    }
}