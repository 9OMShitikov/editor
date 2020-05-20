#include "EventManager.h"

void EventManager::addWindowObj(WindowObj *obj, sf::RenderWindow *window_ptr) {
    window_objects_.emplace_back(obj, window_ptr);
}

void EventManager::deleteWindowObj(WindowObj *obj, sf::RenderWindow *window_ptr) {
    for (size_t i = 0; i < window_objects_.size(); ++i) {
        if (window_objects_[i].window_ptr == window_ptr && window_objects_[i].obj_ptr == obj) {
            window_objects_.erase(window_objects_.begin() + i);
            return ;
        }
    }
}

void EventManager::checkEvents(sf::Event &event, const sf::Vector2f &scale, sf::RenderWindow *window_ptr) const {
    sf::Vector2f pos = {0, 0};

    if ((event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        && event.mouseButton.button == sf::Mouse::Left) {
        pos = {static_cast<float>(event.mouseButton.x) / scale.x, static_cast<float>(event.mouseButton.y) / scale.y};
        MouseStatus::setPressedStatus(event.type == sf::Event::MouseButtonPressed);
    } else if (event.type == sf::Event::MouseMoved) {
        pos = {static_cast<float>(event.mouseMove.x) / scale.x, static_cast<float>(event.mouseMove.y) / scale.y};
    } else if (event.type != sf::Event::TextEntered) {
        return;
    }

    for (auto& window_obj : window_objects_) {
        if (window_obj.window_ptr == window_ptr) {
            window_obj.obj_ptr->AcceptEvent(event, pos);
        }
    }
}