#ifndef LEVELGENERATOR_PALETTE_H
#define LEVELGENERATOR_PALETTE_H

#include <vector>
#include "Button.h"
#include "../Managers/TextureManager.h"
#include "../Managers/LayoutManager.h"
#include "../Managers/EventManager.h"

class Palette : public sf::Drawable, public sf::Transformable {
public:

    explicit Palette(sf::Vector2f pos, sf::Vector2f sizes, TextureManager* tex_manager, EventManager* click_manager,
                     sf::RenderWindow* window_ptr, const std::vector<TextureName>& landscapes = {});

private:

    void setName(std::string&& name);
    void alignName();
    void fontSizeNormalize();
    void drawBackground(sf::RenderTarget& target) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f pos_;
    sf::Vector2f size_;
    size_t landscape_cnt_;
    sf::Font font_;
    sf::Text name_;
    std::vector<LandscapeButton> landscape_buttons_;
    TextureManager* tex_manager_;
    EventManager* click_manager_;
    sf::RenderWindow* window_ptr_;
};

#endif
