#ifndef EDITOR_MENU_H
#define EDITOR_MENU_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

enum MenuEntryType {
    Save,
    SaveAs,
    Load,
    Empty
};

class FileMenu: public sf::Drawable, sf::Transformable {
public:
    FileMenu(sf::RenderWindow* window, float x, float y, sf::Vector2f size);

    bool HasResult() const;

    void SetResult(MenuEntryType result);

    MenuEntryType GetResult() const;

    void ProcessEvent(sf::Event event);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct MenuEntry {
        sf::RectangleShape entry;
        sf::Text name;
        MenuEntryType type;
    };

    sf::RenderWindow* window_ = nullptr;
    std::vector<MenuEntry> entries_;
    sf::Vector2f size_;
    sf::Font font_;
    int active_position_ = -1;
    MenuEntryType result_ = Empty;
    bool has_result_ = false;
    bool initial_press_ = true;
};


#endif //EDITOR_MENU_H
