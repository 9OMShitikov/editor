#ifndef LEVELGENERATOR_NOTIFICATIONWINDOW_H
#define LEVELGENERATOR_NOTIFICATIONWINDOW_H

#include <SFML/Graphics.hpp>

class NotificationWindow : sf::RenderWindow {
public:
    explicit NotificationWindow(std::string&& message);

    NotificationWindow(const NotificationWindow& ) = delete;
    NotificationWindow(NotificationWindow&& ) = delete;
    NotificationWindow& operator =(const NotificationWindow& ) = delete;
    NotificationWindow& operator =(NotificationWindow&& ) = delete;

    void run();

private:

    void alignWindow();
    void messageConstructor(std::string&&);
    void alignMessage();
    void fontSizeNormalize();

    const sf::Vector2u size_;
    sf::Font font_;
    sf::Text message_;
};

#endif //LEVELGENERATOR_NOTIFICATIONWINDOW_H
