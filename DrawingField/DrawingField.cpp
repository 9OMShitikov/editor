//
// Created by oleg on 20.05.2020.
//

#include "DrawingField.h"
DrawingField::DrawingField(sf::RenderWindow* window, ObjectsPalette* palette,
int height, int width, float x, float y,
float obj_height, float obj_width):
x_(x), y_(y),
window_(window),
palette_(palette),
height_(height),
width_(width),
obj_height_(obj_height),
obj_width_(obj_width) {
    if (!font_.loadFromFile("arial.ttf")) {
        throw std::logic_error("Cannot load font in DrawingField");
    }
    title_.setCharacterSize(20);
    title_.setFont(font_);
    title_.setFillColor(sf::Color::Yellow);

    frame_.setFillColor(sf::Color(0, 0, 0, 0));
    frame_.setOutlineColor(sf::Color::Red);
    frame_.setOutlineThickness(3);
    Rename("Untitled");
    Reshape(width, height);
    ResetFrame(sf::Vector2i(1, 1),
               sf::Vector2i(2, 2));
}

void DrawingField::ProcessEvent(sf::Event event) {
    sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));
    sf::Vector2i coords;
    sf::IntRect box(0, 0, width_, height_);
    if (mouse_coordinats.x < x_) {
        coords.x = -1;
    }
    else {
        coords.x = int((mouse_coordinats.x - x_) / (obj_width_ / width_));
    }
    if (mouse_coordinats.y < y_) {
        coords.y = -1;
    }
    else {
        coords.y = int((mouse_coordinats.y - y_) / (obj_height_ / height_));
    }

    switch (event.type) {
        case (sf::Event::MouseButtonPressed): {
            if (box.contains(coords)) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!left_clicked) {
                        SetUpTexture(coords.x, coords.y, palette_->getChosenTexture());
                    }
                    left_clicked = true;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    if (!right_clicked) {
                        frame_origin_ = coords;
                        std::cout<<"Clicked!"<<std::endl;
                        ResetFrame(coords, coords);
                    }
                    right_clicked = true;
                }
            }
        }
            break;
        case (sf::Event::MouseMoved): {
            if (left_clicked) {
                if (box.contains(coords)) {
                    SetUpTexture(coords.x, coords.y, palette_->getChosenTexture());
                }
            }
            if (right_clicked) {
                sf::Vector2i ang = coords;
                if (ang.x < 0) ang.x = 0;
                if (ang.x >= width_) ang.x = width_ - 1;
                if (ang.y < 0) ang.y = 0;
                if (ang.y >= height_) ang.y = height_ - 1;
                frame_ang_ = ang;
                ResetFrame(frame_origin_, ang);
            }
        }

        case (sf::Event::MouseButtonReleased): {
            if (event.mouseButton.button == sf::Mouse::Left) {
                left_clicked = false;
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                if (right_clicked) {
                    sf::Vector2i ang = coords;
                    if (ang.x < 0) ang.x = 0;
                    if (ang.x >= width_) ang.x = width_ - 1;
                    if (ang.y < 0) ang.y = 0;
                    if (ang.y >= height_) ang.y = height_ - 1;

                    int start_x = std::min(ang.x, frame_origin_.x);
                    int finish_x = std::max(ang.x, frame_origin_.x);
                    int start_y = std::min(ang.y, frame_origin_.y);
                    int finish_y = std::max(ang.y, frame_origin_.y);

                    TextureInfo info = palette_->getChosenTexture();
                    for (int i = start_x; i <= finish_x; ++i)
                        for (int j = start_y; j <= finish_y; ++j)
                            SetUpTexture(i, j, info);
                }
                right_clicked = false;
            }
        }
        default:
            break;
    }
}
void DrawingField::Rename(const std::string& name) {
    name_ = name;
    title_.setString(name);
    title_.setPosition(x_ + obj_width_ / 2 - title_.getLocalBounds().width / 2,
                       y_ - title_.getLocalBounds().height - 10);
}
void DrawingField::Reshape(uint width, uint height) {
    if (width == 0 || height == 0) {
        throw std::logic_error("Bad coords of field");
    }
    width_ = width;
    height_ = height;
    sf::Vector2f origin(x_, y_);
    sf::Vector2f dx(obj_width_ / width, 0);
    sf::Vector2f dy(0, obj_height_ / height);
    vertices_ = sf::VertexArray(sf::Quads, width * height * 4);
    info_.resize(width * height);

    TextureInfo info = palette_->getTexture("stone");

    for (int i = 0 ; i < width; ++i)
        for (int j = 0 ; j < height; ++j) {
            sf::Vector2f pos = origin + sf::Vector2f(obj_width_ / width * float(i),
                                                     obj_height_ / height * float(j));
            sf::Vertex* setup = &vertices_[4 * GlobalPos(i, j)];
            setup[0].position = pos;
            setup[1].position = pos + dx;
            setup[2].position = pos + dx + dy;
            setup[3].position = pos + dy;

            SetUpTexture(i, j, info);
        }
}

void DrawingField::SetUpTexture(uint x, uint y, const TextureInfo& info) {
    sf::Vector2f info_pos = sf::Vector2f(info.borders.left, info.borders.top);
    sf::Vector2f info_dx = sf::Vector2f(info.borders.width, 0);
    sf::Vector2f info_dy = sf::Vector2f(0, info.borders.height);
    uint g_pos = GlobalPos(x, y);
    info_[g_pos] = info;

    sf::Vertex* setup = &vertices_[4 * GlobalPos(x, y)];
    setup[0].texCoords = info_pos;
    setup[1].texCoords = info_pos + info_dx;
    setup[2].texCoords = info_pos + info_dx + info_dy;
    setup[3].texCoords = info_pos + info_dy;
}

void DrawingField::ResetFrame(sf::Vector2i start, sf::Vector2i finish) {
    uint start_x = std::min(start.x, finish.x);
    uint finish_x = std::max(start.x, finish.x);

    uint start_y = std::min(start.y, finish.y);
    uint finish_y = std::max(start.y, finish.y);

    sf::Vector2f pos(x_ + obj_width_ / width_ * start_x,
                     y_ + obj_height_ / height_ * start_y);

    sf::Vector2f shape(obj_width_ / width_ * float(1 + finish_x - start_x),
                       obj_height_ / height_ * float(1 + finish_y - start_y));

    frame_.setPosition(pos);
    frame_.setSize(shape);
}

void DrawingField::SaveAs (const std::string& name) {
    Rename(name);
    Save();
}
void DrawingField::Save() {
    std::ofstream out;
    out.open(name_);
    out<<width_<<" "<<height_<<std::endl;

    for (int i = 0; i < width_; ++i)
        for (int j = 0; j < height_; ++j) {
            out << *(info_[GlobalPos(i, j)].name) <<std::endl;
        }
    out.close();
}

void DrawingField::Load(const std::string& name) {
    std::ifstream in;
    try {
        in.open(name);
    }
    catch (...) {
        std::cout<<"failed_to_open"<<std::endl;
        return;
    }
    Rename(name);
    in >> width_ >> height_;

    Reshape(width_, height_);
    std::string tex_name;
    for (int i = 0; i < width_; ++i)
        for (int j = 0; j < height_; ++j) {
            in >> tex_name;
            SetUpTexture(i, j, palette_->getTexture(tex_name));
        }
    in.close();
}

void DrawingField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(title_, states);
    sf::RenderStates new_states = states;
    new_states.texture = palette_->getGlobalTexture();
    target.draw(vertices_, new_states);

    if (right_clicked) {
        target.draw(frame_);
    }
}

uint DrawingField::GlobalPos(uint x, uint y) const {
    return x + y * width_;
}
