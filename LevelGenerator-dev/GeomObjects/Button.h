#ifndef LEVELGENERATOR_BUTTON_H
#define LEVELGENERATOR_BUTTON_H

#include <SFML/Graphics.hpp>
#include "../Managers/TextureManager.h"
#include "../YAML API/DefiningYAMLFormat.h"
#include "TileMap.h"
#include <cassert>

enum class ButtonStatus {
    Activated,
    Deactivated
};

class Button : public WindowObj {

public:

    explicit Button(sf::Vector2f pos, sf::Vector2f sizes, TextureManager* manager = nullptr,
        TextureName texture = TextureName::Emptiness, const sf::Color& color = sf::Color::White);
    ~Button() override = default;

    sf::Vector2f getPos() const;
    sf::Vector2f getSize() const override;
    void setSize(const sf::Vector2f&) override;
    sf::FloatRect getLocalBounds() const;
    TextureName getTextureName() const;
    void setName(const std::string& name);
    void AcceptEvent(sf::Event&, const sf::Vector2f &scale) override;
    virtual void click() {};

private:

    void nameConstructor();
    void spriteConstructor();
    void setTexture(TextureName texture);
    void setDefaultTexture(sf::Color color);
    void alignName();
    void fontSizeNormalize();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::Vector2f pos_;
    sf::Vector2f size_;
    sf::RectangleShape sprite_;
    TextureManager* manager_;
    TextureName texture_name_;
    sf::Font font_;
    sf::Text name_{};
};

//////////////////////////////////////////////

class LandscapeButton : public Button {
public:
    explicit LandscapeButton(sf::Vector2f pos, sf::Vector2f sizes, TextureManager* manager, TextureName texture) :
        Button(pos, sizes, manager, texture) {
            setStatus(ButtonStatus::Deactivated);
    };
    ~LandscapeButton() override = default;

    void click() override;

private:
    void setStatus(ButtonStatus);

    ButtonStatus status_ = ButtonStatus::Deactivated;
};

class ClearButton : public Button {
public:
    explicit ClearButton(sf::Vector2f pos, sf::Vector2f sizes, TileMap* map,
                const sf::Color& color = sf::Color::White, TextureManager* tex_manager = nullptr):
            Button(pos, sizes, tex_manager, TextureName::Emptiness, color),
            map_(map) {
        setName("Clear Map");
    };
    ~ClearButton() override = default;

    void click() override;

private:
    TileMap* map_ = nullptr;
};


class SaveButton : public Button {
public:
    explicit SaveButton(sf::Vector2f pos, sf::Vector2f sizes, TileMap* map,
            const sf::Color& color = sf::Color::White, TextureManager* tex_manager = nullptr):
        Button(pos, sizes, tex_manager, TextureName::Emptiness, color),
        map_(map) {
        setName("Save Map");
    };
    ~SaveButton() override = default;

    void click() override;

private:
    void write_map(std::string&& file_name) const;

    TileMap* map_ = nullptr;
};

class OpenButton : public Button {
public:
    explicit OpenButton(sf::Vector2f pos, sf::Vector2f sizes, TileMap* map,
            const sf::Color& color = sf::Color::White, TextureManager* tex_manager = nullptr):
        Button(pos, sizes, tex_manager, TextureName::Emptiness, color),
        map_(map) {
        setName("Open Map");
    };
    ~OpenButton() override = default;

    void click() override;

private:
    static void read_error(std::string&& error_description);
    void read_map(std::string&& file_name) const;

    TileMap* map_ = nullptr;
};


#endif
