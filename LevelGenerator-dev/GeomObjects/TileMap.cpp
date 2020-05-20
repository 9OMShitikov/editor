#include "TileMap.h"
#include "../Managers/MouseStatus.h"

TileMap::TileMap(sf::Vector2f position, sf::Vector2u tile_size, size_t width, size_t height,
                TextureManager *texture_manager, std::vector<TextureName> &&info) :
        pos_(position),
        tile_size_(tile_size),
        width_(width),
        height_(height),
        texture_manager_(texture_manager),
        m_vertices_(sf::VertexArray(sf::Quads, width_ * height_ * 4)) {

        if (info.size() == width_ * height_) {
            info_ = std::move(info);
        } else {
            info_.resize(width_ * height_, TextureName::Emptiness);
        }

        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = 0; j < width_; ++j) {

                int tile_number = get_index(i, j);
                sf::Vertex *quad = &m_vertices_[tile_number * 4];

                quad[0].position = pos_ + sf::Vector2f(j * tile_size_.x, i * tile_size_.y);
                quad[1].position = pos_ + sf::Vector2f((j + 1) * tile_size_.x, i * tile_size_.y);
                quad[2].position = pos_ + sf::Vector2f((j + 1) * tile_size_.x, (i + 1) * tile_size_.y);
                quad[3].position = pos_ + sf::Vector2f(j * tile_size_.x, (i + 1) * tile_size_.y);

                updateTileTexture(tile_number);
            }
        }
}

sf::Vector2f TileMap::getPos() const {
    return pos_;
}

sf::Vector2f TileMap::getSize() const {
    return sf::Vector2f(tile_size_.x * width_, tile_size_.y * height_);
}

sf::FloatRect TileMap::getLocalBounds() const {
    return sf::FloatRect(getPos(), getSize());
}

sf::Vector2u TileMap::getTileSize() const {
    return tile_size_;
}

sf::Vector2u TileMap::getSizeInTiles() const {
    return sf::Vector2u(width_, height_);
}

TextureName TileMap::getTextureName(int i, int j) const {
    return info_[get_index(i, j)];
}

TextureName TileMap::getTextureName(int tile_num) const {
    return info_[tile_num];
}

const std::vector<TextureName>& TileMap::getInfo() const {
    return info_;
}


void TileMap::click(sf::Vector2f click_pos) {
    click_pos -= pos_;
    size_t tile_number = get_index(static_cast<size_t>(click_pos.y) / tile_size_.y,
                                   static_cast<size_t>(click_pos.x) / tile_size_.x);

    if (info_[tile_number] != MouseStatus::getLandscape()) {
        info_[tile_number] = MouseStatus::getLandscape();
        updateTileTexture(tile_number);
    }
}

void TileMap::clear() {
    for (size_t tile_num = 0; tile_num < info_.size(); ++tile_num) {
        if (getTextureName(tile_num) != TextureName::Emptiness) {
            info_[tile_num] = TextureName::Emptiness;
            updateTileTexture(tile_num);
        }
    }
}

void TileMap::loadInfo(std::vector<TextureName>&& new_info) {
    info_ = std::move(new_info);
    for (size_t tile_number = 0; tile_number < info_.size(); ++tile_number) {
        updateTileTexture(tile_number);
    }
}

void TileMap::AcceptEvent(sf::Event& event, const sf::Vector2f &pos) {
    if (MouseStatus::getPressedStatus() && getLocalBounds().contains(pos)) {
        if (MouseStatus::getLandscapeButton() != nullptr) {
            click(pos);
        }
    }
}


/////////////////////////////////////

void TileMap::updateTileTexture(int tile_number) {
    sf::Vertex* quad = &m_vertices_[tile_number * 4];
    sf::IntRect tex_rect = texture_manager_->getRect(info_[tile_number]);
    quad[0].texCoords = sf::Vector2f(tex_rect.left, tex_rect.top);
    quad[1].texCoords = sf::Vector2f(tex_rect.left + tex_rect.width, tex_rect.top);
    quad[2].texCoords = sf::Vector2f(tex_rect.left + tex_rect.width, tex_rect.top + tex_rect.height);
    quad[3].texCoords = sf::Vector2f(tex_rect.left, tex_rect.top + tex_rect.height);
}

void TileMap::drawBackground(sf::RenderTarget &target) const {
    sf::RectangleShape map_background(sf::Vector2f(width_ * tile_size_.x, height_ * tile_size_.y));
    map_background.setPosition(pos_);
    map_background.setFillColor(sf::Color::White);
    map_background.setOutlineThickness(1);
    map_background.setOutlineColor(sf::Color::Black);
    target.draw(map_background);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawBackground(target);
    states.texture = texture_manager_->getAllTextures();
    target.draw(m_vertices_, states);
}