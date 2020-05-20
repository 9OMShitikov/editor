#include "TextureManager.h"

std::string getTextureName(TextureName tex_name) {
    switch (tex_name) {
        case TextureName::Grass:
    return "Grass";
        case TextureName::River:
    return "River";
        case TextureName::Tree:
    return "Tree";
        case TextureName::Gravel:
    return "Gravel";
        case TextureName::Emptiness:
    return "Emptiness";
        default:
    return "";
    }
}


TextureManager::TextureManager(const std::string &file, const std::vector<std::pair<TextureName, sf::IntRect>> &data) :
    texture_file_(file) {
        if (!all_textures_.loadFromFile(file)) {
            throw std::runtime_error("File cannot be opened");
        }

        data_.reserve(data.size());
        for (auto& [texture_name, rect]: data) {
            data_.emplace_back(texture_name, rect, file);
        }
        sf::IntRect rect(data_.size() * data_[0].borders.width, 0, 0, 0);
        data_.emplace_back(TextureName::Emptiness, rect, file);
}

sf::IntRect TextureManager::getRect(TextureName name) const {
    for (auto& elem: data_) {
        if (elem.texture_name == name) {
            return elem.borders;
        }
    }
    throw std::runtime_error("There is no texture with this name");
}

const sf::Texture* TextureManager::getTexture(TextureName name) const {
    for (auto& elem: data_) {
        if (elem.texture_name == name) {
            return &elem.texture;
        }
    }
    throw std::runtime_error("There is no texture with this name");
}

const sf::Texture* TextureManager::getAllTextures() const {
    return &all_textures_;
}

std::string TextureManager::getTextureFile() const {
    return texture_file_;
}

size_t TextureManager::getTextureCnt() const {
    return data_.size();
}
