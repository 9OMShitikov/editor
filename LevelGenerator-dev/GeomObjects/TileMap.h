#ifndef LEVELGENERATOR_TileMap_H
#define LEVELGENERATOR_TileMap_H

#include <SFML/Graphics.hpp>
#include <cassert>
#include "../Managers/TextureManager.h"
#include "WindowObj.h"

class TileMap : public WindowObj {
public:

    explicit TileMap(sf::Vector2f position, sf::Vector2u tile_size, size_t width, size_t height,
        TextureManager* texture_manager, std::vector<TextureName>&& info = {});

    sf::Vector2f getPos() const;
    sf::Vector2f getSize() const override;
    sf::Vector2u getTileSize() const;
    sf::Vector2u getSizeInTiles() const;
    sf::FloatRect getLocalBounds() const;

    TextureName getTextureName(int i, int j) const;
    TextureName getTextureName(int tile_num) const;
    const std::vector<TextureName>& getInfo() const;

    void AcceptEvent(sf::Event&, const sf::Vector2f &pos) override;
    void click(sf::Vector2f click_pos);
    void clear();
    void loadInfo(std::vector<TextureName>&&);


private:

    size_t get_index(size_t i, size_t j) const {
        assert(i < height_ && j < width_);
        return i * width_ + j;
    }

    void updateTileTexture(int tile_number);
    void drawBackground(sf::RenderTarget& target) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f pos_;
    size_t width_;
    size_t height_;
    sf::Vector2u tile_size_;
    sf::VertexArray m_vertices_;
    TextureManager* texture_manager_;
    std::vector<TextureName> info_{};
};


#endif //LEVELGENERATOR_TileMap_H
