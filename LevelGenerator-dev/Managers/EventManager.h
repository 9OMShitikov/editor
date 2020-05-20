#ifndef LEVELGENERATOR_EVENTMANAGER_H
#define LEVELGENERATOR_EVENTMANAGER_H

#include "../GeomObjects/Button.h"
#include "../GeomObjects/TileMap.h"
#include "../GeomObjects/InputBox.h"
#include "MouseStatus.h"

class EventManager {
public:
    explicit EventManager() = default;
    EventManager(const EventManager& ) = delete;
    EventManager(EventManager&& ) = delete;
    EventManager& operator=(const EventManager& ) = delete;
    EventManager& operator=(EventManager&& ) = delete;

    void addWindowObj(WindowObj* obj, sf::RenderWindow* window_ptr = nullptr);
    void deleteWindowObj(WindowObj* obj, sf::RenderWindow* window_ptr = nullptr);
    void checkEvents(sf::Event& event, const sf::Vector2f& scale, sf::RenderWindow* window_ptr) const ;

private:

    struct WindowObject {
        WindowObject(WindowObj* obj, sf::RenderWindow* window) :
            obj_ptr(obj),
            window_ptr(window) {};

        WindowObj* obj_ptr;
        sf::RenderWindow* window_ptr;
    };

    std::vector<WindowObject> window_objects_ {};
};

#endif
