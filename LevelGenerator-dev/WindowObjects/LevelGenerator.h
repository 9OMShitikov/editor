#ifndef LEVELGENERATOR_LEVELGENERATOR_H
#define LEVELGENERATOR_LEVELGENERATOR_H

#include <SFML/Graphics.hpp>
#include "../Managers/LayoutManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"
#include "../GeomObjects/TileMap.h"
#include "../GeomObjects/Palette.h"
#include "../GeomObjects/Minimap.h"

class LevelGenerator : public sf::RenderWindow {
public:
    explicit LevelGenerator(const std::vector<TextureName>& palette_landscapes, TextureManager* texture_manager,
                            const sf::VideoMode& window = sf::VideoMode::getDesktopMode(), EventManager* click_manager = nullptr);

    LevelGenerator(const LevelGenerator& ) = delete;
    LevelGenerator(LevelGenerator&& ) = delete;
    LevelGenerator& operator =(const LevelGenerator& ) = delete;
    LevelGenerator& operator =(LevelGenerator&& ) = delete;

    ~LevelGenerator() override {
        for (Button* service_button: service_buttons_) {
            delete service_button;
        }
        if (init_event_manager_) {
            delete event_manager_;
        }
    }

    void run();


private:

    void alignWindow();
    void sizeCheck() const;

    sf::Vector2f size_;
    TextureManager* texture_manager_;
    LayoutManager space_manager_;
    bool init_event_manager_;
    EventManager* event_manager_;
    TileMap map_;
    Minimap minimap_;
    Palette palette_;
    std::vector<Button*> service_buttons_;
};

#endif