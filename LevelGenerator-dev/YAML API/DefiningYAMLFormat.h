#ifndef LEVELGENERATOR_DEFININGYAMLFORMAT_H
#define LEVELGENERATOR_DEFININGYAMLFORMAT_H

#include "Specialized Classes.h"

namespace YAML {

    template<typename T>
    struct convert<std::vector<T>> {
        static Node encode(const std::vector<T> &rhs) {
            std::ostringstream out("");
            out << "[";
            for (int i = 0; i < rhs.size(); ++i) {
                out << rhs[i];
                if (i != rhs.size() - 1) {
                    out << ", ";
                } else {
                    out << "]";
                }
            }
            return YAML::Node(out.str());
        }

        static bool decode(const Node &node, std::vector<T> &rhs) {
            rhs.clear();
            char c;
            T elem;
            std::istringstream in(node.as<std::string>());

            in >> c;
            while (c != ']') {
                in >> elem;
                rhs.push_back(elem);
                in >> c;
            }
            return true;
        }
    };

    template<>
    struct convert<sf::IntRect> {
        static Node encode(const sf::IntRect& rhs) {
            Node node;
            node["left"] = rhs.left;
            node["top"] = rhs.top;
            node["width"] = rhs.width;
            node["height"] = rhs.height;
            return node;
        }

        static bool decode(const Node& node, sf::IntRect& rhs) {
            rhs = sf::IntRect(node["left"].as<int>(), node["top"].as<int>(), node["width"].as<int>(), node["height"].as<int>());
            return true;
        }
    };

    template<>
    struct convert<GraphicalComponent> {
        static Node encode(const GraphicalComponent& rhs) {
            Node node;
            node["sprite_path"] = rhs.sprite_path;
            node["sprite_pos"] = rhs.sprite_pos;
            node["layer"] = rhs.layer;
            return node;
        }

        static bool decode(const Node& node, GraphicalComponent& rhs) {
            rhs.sprite_path = node["sprite_path"].as<std::string>();
            rhs.sprite_pos = node["sprite_pos"].as<sf::IntRect>();
            rhs.layer = node["layer"].as<std::string>();
            return true;
        }
    };

    template<>
    struct convert<PhysicalComponent> {
        static Node encode(const PhysicalComponent& rhs) {
            Node node;
            node["on_grid"] = rhs.on_grid;
            node["is_static"] = rhs.is_static;
            node["is_player_controlled"] = rhs.is_player_controlled;
            return node;
        }

        static bool decode(const Node& node, PhysicalComponent& rhs) {
            rhs.on_grid = node["on_grid"].as<bool>();
            rhs.is_static = node["is_static"].as<bool>();
            rhs.is_player_controlled = node["is_player_controlled"].as<bool>();
            return true;
        }
    };

    template<>
    struct convert<GameEntity> {
        static Node encode(const GameEntity& rhs) {
            Node node;
            node["entity_id"] = rhs.id;
            node["name"] = rhs.name;
            node["graph_comp"] = rhs.graph_comp;
            node["phys_comp"] = rhs.phys_comp;
            return node;
        }

        static bool decode(const Node& node, GameEntity& rhs) {
            rhs.name = node["name"].as<std::string>();
            rhs.id = node["entity_id"].as<int>();
            rhs.graph_comp = node["graph_comp"].as<GraphicalComponent>();
            return true;
        }
    };

    template<>
    struct convert<LandscapeObject> {
        static Node encode(const LandscapeObject& rhs) {
            return convert<GameEntity>::encode(rhs);
        }

        static bool decode(const Node& node, LandscapeObject& rhs) {
            convert<GameEntity>::decode(node, rhs);
            return true;
        }
    };

    template<>
    struct convert<SchematicMap> {
        static Node encode(const SchematicMap& rhs) {
            Node node;
            node["Map"]["width"] = rhs.width;
            node["Map"]["height"] = rhs.height;
            for (int i = 0; i < rhs.height; ++i) {
                std::vector<int> map_str;
                for (int j = 0; j < rhs.width; ++j) {
                    map_str.push_back(static_cast<int>(rhs.tiles[i * rhs.width + j]));
                }
                node["Map"]["tiles"].push_back(map_str);
            }
            return node;
        }

        static bool decode(const Node& node, SchematicMap& rhs) {
            rhs.width = node["Map"]["width"].as<int>();
            rhs.height = node["Map"]["height"].as<int>();
            rhs.tiles.clear();

            for (int i = 0; i < rhs.height; ++i) {
                for (auto elem : node["Map"]["tiles"][i].as<std::vector<int>>()) {
                    rhs.tiles.push_back(static_cast<TextureName>(elem));
                }
            }
            return true;
        }
    };

    template<>
    struct convert<MapObject> {
        static Node encode(const MapObject& rhs) {
            Node node(convert<GameEntity>::encode(rhs));
            //       node["coordinates"] = rhs.coord;
            return node;
        }

        static bool decode(const Node& node, MapObject& rhs) {
            convert<GameEntity>::decode(node, rhs);
            //         rhs.coord = node["coordinates"].as<std::vector<sf::Vector2f>>();
            return true;
        }
    };
}

#endif //LEVELGENERATOR_DEFININGYAMLFORMAT_H
