
#ifndef EDITOR_DRAWINGFIELD_H
#define EDITOR_DRAWINGFIELD_H

#include <SFML/Graphics.hpp>
#include "../ObjectsPalette/ObjectsPalette.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdio>
#include <iostream>


class DrawingField: public sf::Drawable, public sf::Transformable {
public:
    DrawingField(sf::RenderWindow* window, ObjectsPalette* palette,
                 int height, int width, float x, float y,
                 float obj_height, float obj_width);

    void ProcessEvent(sf::Event event);
    void Rename(const std::string& name);
    void Reshape(uint width, uint height);

    void SetUpTexture(uint x, uint y, const TextureInfo& info);

    void ResetFrame(sf::Vector2i start, sf::Vector2i finish);

    void SaveAs (const std::string& name);
    void Save();
    void Load(const std::string& name);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    uint GlobalPos(uint x, uint y) const;

    bool draw_frame_ = false;
    sf::Vector2i frame_origin_, frame_ang_;
    sf::VertexArray vertices_;
    sf::RenderWindow* window_;
    sf::Text title_;
    sf::Font font_;
    sf::RectangleShape frame_;

    float x_, y_;
    uint width_;
    uint height_;
    float obj_width_;
    float obj_height_;
    ObjectsPalette* palette_;
    bool left_clicked = false, right_clicked = false;
    std::string name_;
    std::vector<TextureInfo> info_;
};

#endif //EDITOR_DRAWINGFIELD_H
