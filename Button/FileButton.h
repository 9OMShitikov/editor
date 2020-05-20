
#ifndef EDITOR_FILEBUTTON_H
#define EDITOR_FILEBUTTON_H
#include "Button.h"
#include "../DrawingField/DrawingField.h"

class DrawingField;

class FileButton: public Button {
public:
    FileButton(float x, float y, float x_size, float y_size, sf::RenderWindow* window,
               DrawingField* field);

    void ProcessEvent(const sf::Event event) override;

    void ProcessPress() override;

    void ProcessRelease() override;

    void Process() override;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Text text_;
    sf::Font font_;

    FileMenu* menu_ = nullptr;
    DrawingField* field_;
};


#endif //EDITOR_FILEBUTTON_H
