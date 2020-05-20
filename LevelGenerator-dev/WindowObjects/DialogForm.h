#ifndef LEVELGENERATOR_DIALOGFORM_H
#define LEVELGENERATOR_DIALOGFORM_H

#include "SFML/Graphics.hpp"
#include "../Managers/EventManager.h"
#include "../Managers/DialogLayoutForm.h"

class DialogForm : public sf::RenderWindow {
public:
    explicit DialogForm(const std::string& form_name, const DialogLayoutForm& layout,
            EventManager* click_manager = nullptr):

        sf::RenderWindow(sf::VideoMode(layout.getSize().x, layout.getSize().y), form_name,
                         sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(0, 0, 8)),
        size_(layout.getSize()),
        init_click_manager_(click_manager == nullptr),
        click_manager_(init_click_manager_ ? new EventManager() : click_manager),
        window_objects_(layout.getObjects()) {

            if (!font_.loadFromFile("arial.ttf")) {
                throw std::runtime_error("It is not possible to load the font");
            }
            alignWindow();
    }


    DialogForm(const DialogForm& ) = delete;
    DialogForm(DialogForm&& ) = delete;
    DialogForm& operator=(const DialogForm& ) = delete;
    DialogForm& operator=(DialogForm&& ) = delete;

    ~DialogForm() override {
        if (init_click_manager_) {
            delete click_manager_;
        }
    }

    void EnterPressed(InputBox* message_box) {

    }

    void run() {
        while (isOpen()) {
            sf::Event event{};
            while (pollEvent(event))
            {
                if (event.type == sf::Event::Closed || close_window_) {
                    close();
                }
                click_manager_->checkEvents(event, sf::Vector2f(1, 1), this);
            }
            clear(sf::Color(240, 240, 240));

            for (auto window_obj: window_objects_) {
                draw(*window_obj);
            }
            display();
        }
    }

private:

    void alignWindow() {
        size_t x_centre = (sf::VideoMode::getDesktopMode().width - size_.x) / 2;
        size_t y_centre = (sf::VideoMode::getDesktopMode().height - size_.y) / 2;
        setPosition(sf::Vector2i(x_centre, y_centre));
    }

    bool close_window_ = false;
    bool init_click_manager_ = false;

    std::vector<WindowObj*> window_objects_;
    sf::Vector2u size_;
    sf::Font font_;
    EventManager* click_manager_;
};

#endif //LEVELGENERATOR_DIALOGFORM_H
