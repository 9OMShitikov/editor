#ifndef LEVELGENERATOR_MINIMAP_H
#define LEVELGENERATOR_MINIMAP_H

#include "TileMap.h"

class Minimap : public sf::Drawable, public sf::Transformable {
public:
    explicit Minimap(sf::Vector2f pos, sf::Vector2f size, TileMap* map) :
        map_(map),
        pos_(pos),
        size_(size) {};

private:

    void draw_background(sf::RenderTarget& target) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    TileMap* map_;
    sf::Vector2f pos_;
    sf::Vector2f size_;
};

#endif //LEVELGENERATOR_MINIMAP_H
