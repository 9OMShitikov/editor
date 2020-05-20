#include "Minimap.h"

void Minimap::draw_background(sf::RenderTarget &target) const {
    sf::RectangleShape map_background(size_);
    map_background.setPosition(pos_);
    map_background.setFillColor(sf::Color::White);
    map_background.setOutlineThickness(1);
    map_background.setOutlineColor(sf::Color::Black);
    target.draw(map_background);
}

void Minimap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    draw_background(target);

    sf::View minimap_view(sf::FloatRect(map_->getPos(), map_->getSize()));
    sf::Vector2u window_size = target.getSize();
    sf::FloatRect minimap_rect(pos_.x / window_size.x, pos_.y / window_size.y,
                               size_.x / window_size.x, size_.y / window_size.y);
    minimap_view.setViewport(minimap_rect);

    target.setView(minimap_view);
    target.draw(*map_);
    target.setView(target.getDefaultView());
}