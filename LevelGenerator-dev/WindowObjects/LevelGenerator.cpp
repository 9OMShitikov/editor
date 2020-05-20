#include "LevelGenerator.h"

LevelGenerator::LevelGenerator(const std::vector<TextureName> &palette_landscapes, TextureManager *texture_manager,
                               const sf::VideoMode &window, EventManager* click_manager) :
    sf::RenderWindow(window,"Level Generator",sf::Style::Default,sf::ContextSettings(0, 0, 8)),
    size_(this->getSize()),
    texture_manager_(texture_manager),
    space_manager_(window.width, window.height),
    init_event_manager_(click_manager == nullptr),
    event_manager_(init_event_manager_ ? new EventManager() : click_manager),
    map_(space_manager_.getPos(GeomObjType::Map), sf::Vector2u(32, 32), space_manager_.getSize(GeomObjType::Map).x / 32,
         space_manager_.getSize(GeomObjType::Map).y / 32,texture_manager_),
    minimap_(space_manager_.getPos(GeomObjType::Minimap), space_manager_.getSize(GeomObjType::Minimap), &map_),
    palette_(space_manager_.getPos(GeomObjType::Palette), space_manager_.getSize(GeomObjType::Palette),
             texture_manager_, event_manager_, this, palette_landscapes) {

        sizeCheck();
        alignWindow();
        sf::Color button_color = sf::Color(135, 206, 250);
        Button* save_button = new SaveButton(space_manager_.getPos(GeomObjType::SaveButton),
                                             space_manager_.getSize(GeomObjType::SaveButton),
                                             &map_, button_color, texture_manager_);

        Button* open_button = new OpenButton(space_manager_.getPos(GeomObjType::OpenButton),
                                             space_manager_.getSize(GeomObjType::OpenButton),
                                             &map_, button_color, texture_manager_);

        Button* clear_button = new ClearButton(space_manager_.getPos(GeomObjType::RunButton),
                                               space_manager_.getSize(GeomObjType::RunButton),
                                               &map_, button_color, texture_manager_);

        service_buttons_ = {save_button, open_button, clear_button};

        event_manager_->addWindowObj(&map_, this);
        for (auto& button : service_buttons_) {
            event_manager_->addWindowObj(button, this);
        }
}

void LevelGenerator::alignWindow() {
    size_t x_centre = (static_cast<float>(sf::VideoMode::getDesktopMode().width) - size_.x) / 2;
    size_t y_centre = (static_cast<float>(sf::VideoMode::getDesktopMode().height) - size_.y) / 2;
    setPosition(sf::Vector2i(x_centre, y_centre));
}

void LevelGenerator::sizeCheck() const {
    if (size_.x < 650 || size_.y < 430) {
        throw std::invalid_argument("Minimum map size is 650x430");
    }
}


void LevelGenerator::run()  {
    while (isOpen()) {
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                close();
            sf::Vector2f scale = {getSize().x / size_.x, getSize().y / size_.y};
            event_manager_->checkEvents(event, scale, this);
        }
        clear(sf::Color(240, 240, 240));

        draw(map_);
        draw(palette_);
        for (auto button: service_buttons_) {
            draw(*button);
        }
        draw(minimap_);
        display();
    }
}
