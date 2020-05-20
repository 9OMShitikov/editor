#ifndef EDITOR_OBJECTSPALETTE_H
#define EDITOR_OBJECTSPALETTE_H
#include <SFML/Graphics.hpp>

#include "../Button/TextureButton.h"
#include <vector>
#include <string>

struct TextureInfo {
    sf::Texture* texture = nullptr;
    std::string* name = nullptr;
    sf::IntRect borders;
};

class ObjectsPalette: public sf::Drawable, sf::Transformable {
public:
    ObjectsPalette(float x, float y, float x_size, float y_size, sf::RenderWindow* window);

    void ProcessEvent(const sf::Event event);

    TextureInfo getChosenTexture();

    TextureInfo getTexture(const std::string& name);
    sf::Texture* getGlobalTexture();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    size_t buttons_count = 4;
    sf::RenderWindow* window_;
    sf::Texture global_texture_;
    std::vector <sf::Texture> textures_;
    std::vector <std::string> names_;
    std::vector <TextureButton> buttons_;
};


#endif //EDITOR_OBJECTSPALETTE_H
