
#ifndef EDITOR_ENTERTEXT_H
#define EDITOR_ENTERTEXT_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class EnterText: public sf::Drawable, sf::Transformable {
public:
    EnterText(sf::RenderWindow *window, float x, float y, float len);

    bool IsActive() const;

    sf::FloatRect getLocalBounds();

    void ProcessEvent(const sf::Event event);
    bool GetEnding() const;
    void SetEnding(bool ending);
    void SetActive(bool active);
    void Process();
    bool IsEntered() const;
    std::string GetEntered() const;
    bool ProcessChar(int input);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape line_;
    sf::Text text_;
    sf::Font font_;
    sf::RenderWindow* window_;
    bool is_active_ = false;
    std::string entered_text_ = "";
    bool has_ending_ = false;
    char ending_ = ':';
    bool entered_ = false;
    sf::Clock timer;
};


#endif //EDITOR_ENTERTEXT_H
