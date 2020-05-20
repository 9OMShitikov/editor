#include <iostream>
#include "WindowObjects/LevelGenerator.h"
#include "WindowObjects/NotificationWindow.h"
#include <yaml-cpp/yaml.h>

std::vector<std::pair<TextureName, sf::IntRect>> get_marking() {
    std::vector<std::pair<TextureName, sf::IntRect>> data(4);
    for (int i = 0; i < 4; ++i) {
        data[i].first = static_cast<TextureName>(i);
        data[i].second = sf::IntRect(i * 32, 0, 32, 32);
    }
    return data;
}

int main() {
    size_t window_width = 1300;
    size_t window_height = 800;
    sf::VideoMode window = sf::VideoMode(window_width, window_height);


    std::string textures_file = "terrains.png";
    TextureManager texture_manager(textures_file, get_marking());


    try {
        std::vector<TextureName>palette_landscapes
                = {TextureName::Grass, TextureName::Tree, TextureName::Gravel, TextureName::River};

        LevelGenerator generator(palette_landscapes, &texture_manager, window);
        generator.run();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
    return 0;
}

//int main() {
//    size_t window_width = 1300;
//    size_t window_height = 800;
//    sf::VideoMode size = sf::VideoMode(window_width, window_height);
//    try {
//        DialogLayoutForm layout_form(sf::Vector2f(1300, 300));
//        auto* a = new Button({0, 0}, {0, 0}, nullptr, TextureName::Emptiness, sf::Color(152, 251, 152));
//        auto* b = new Button({0, 0}, {0, 0}, nullptr, TextureName::Emptiness, sf::Color(152, 251, 152));
//        layout_form.addChoiceQuestion("kekkos", 0);
//        layout_form.addChoiceQuestion("kekkos", 0);
//        layout_form.addChoiceQuestion("kekkos", 2, a, b);
//        DialogForm dialog_form("Questionnaire", layout_form);
//        dialog_form.run();
//    } catch (std::exception& e) {
//        std::cout << e.what() << std::endl;
//        exit(1);
//    }
//    return 0;
//}