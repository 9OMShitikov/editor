#ifndef LEVELGENERATOR_SPECIALIZED_CLASSES_H
#define LEVELGENERATOR_SPECIALIZED_CLASSES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>


struct GraphicalComponent {
    explicit GraphicalComponent(const std::string& file_name, sf::IntRect obj_pos, std::string&& obj_type):
            sprite_path(file_name),
            sprite_pos(obj_pos),
            layer(std::move(obj_type)) {};

    explicit GraphicalComponent():
            sprite_path(""), layer(""), sprite_pos(0, 0, 0, 0) {};


    std::string sprite_path;
    std::string layer;
    sf::IntRect sprite_pos;
};

struct PhysicalComponent {
    bool on_grid = true;
    bool is_static = true;
    bool is_player_controlled = false;
};

struct GameEntity {
protected:
    explicit GameEntity() = default;
    explicit GameEntity(int obj_id, std::string&& obj_name, sf::IntRect tex_pos,
                        const std::string& file_name, std::string&& layer):
            id(obj_id),
            name(std::move(obj_name)),
            graph_comp(file_name, tex_pos, std::move(layer)) {};

public:
    int id;
    std::string name;
    GraphicalComponent graph_comp;
    PhysicalComponent phys_comp;
};

struct LandscapeObject : GameEntity {
    explicit LandscapeObject() = default;
    explicit LandscapeObject(TextureName tex_name, const std::string& file_name ,sf::IntRect tex_pos):
            GameEntity(static_cast<int>(tex_name), getTextureName(tex_name), tex_pos, file_name, "BACKGROUND") {

        phys_comp.on_grid = true;
        phys_comp.is_static = (tex_name != TextureName::River);
        phys_comp.is_player_controlled = (tex_name == TextureName::Grass || tex_name == TextureName::Gravel);
    };
};

struct MapObject : GameEntity {
    explicit MapObject() = default;
    explicit MapObject(int id, std::string&& obj_name, const std::string& file_name,
                       sf::IntRect tex_pos, std::vector<sf::Vector2f>&& obj_coord):
            GameEntity(id, std::move(obj_name), tex_pos, file_name, "FOREGROUND"),
            coord(std::move(obj_coord)) {

        phys_comp.on_grid = false;
        phys_comp.is_static = false;
        phys_comp.is_player_controlled = true;
    };

    std::vector<sf::Vector2f> coord;
};

struct SchematicMap {
    explicit SchematicMap() = default;
    explicit SchematicMap(size_t map_width, size_t map_height, const std::vector<TextureName>& map_tiles) :
        width(map_width),
        height(map_height),
        tiles(map_tiles) {};

    int width = 0, height = 0;
    std::vector<TextureName> tiles;
};


#endif //LEVELGENERATOR_SPECIALIZED_CLASSES_H
