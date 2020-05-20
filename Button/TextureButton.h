
#ifndef EDITOR_TEXTUREBUTTON_H
#define EDITOR_TEXTUREBUTTON_H
#include "Button.h"

class ObjectsPalette;

class TextureButton: public Button {
public:
    TextureButton(float x, float y, float x_size, float y_size,
                  sf::Texture* texture,
                  std::vector<TextureButton>& buttons,
                  ObjectsPalette* parent,
                  sf::RenderWindow* window);

    void ProcessEvent(const sf::Event event) override;

    void ProcessPress() override;

    void ProcessRelease() override;

    void Process() override;
private:
    float border_size_ = 4;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ObjectsPalette* parent_ = nullptr;
    std::vector<TextureButton>& buttons_;
    sf::Texture* texture_;
};


#endif //EDITOR_TEXTUREBUTTON_H
