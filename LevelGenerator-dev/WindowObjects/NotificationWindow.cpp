#include "NotificationWindow.h"

NotificationWindow::NotificationWindow(std::string&& message) :
    sf::RenderWindow(sf::VideoMode(500, 100),"Notification Window",
            sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(0, 0, 8)),
    size_(sf::Vector2u(500, 100)) {

        alignWindow();
        messageConstructor(std::move(message));
}

void NotificationWindow::run() {
    while (isOpen()) {
        sf::Event event{};
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                close();
            }
        }
        clear(sf::Color(240, 240, 240));
        draw(message_);
        display();
    }
}

/////////////////////////

void NotificationWindow::alignWindow() {
    size_t x_centre = (sf::VideoMode::getDesktopMode().width - size_.x) / 2;
    size_t y_centre = (sf::VideoMode::getDesktopMode().height - size_.y) / 2;
    setPosition(sf::Vector2i(x_centre, y_centre));
}

void NotificationWindow::messageConstructor(std::string&& message) {
    if (!font_.loadFromFile("arial.ttf")) {
        throw std::runtime_error("It is not possible to load the font");
    }

    message_.setFont(font_);
    message_.setString(message);
    message_.setFillColor(sf::Color::Black);
    message_.setCharacterSize(28);

    alignMessage();
    fontSizeNormalize();
}

void NotificationWindow::alignMessage() {
    sf::FloatRect bounds = message_.getLocalBounds();
    sf::Vector2f message_centre = sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    message_.setOrigin(message_centre);
    sf::Vector2f window_centre = sf::Vector2f(static_cast<float>(size_.x) / 2, static_cast<float>(size_.y) / 2);
    message_.setPosition(window_centre);
}

void NotificationWindow::fontSizeNormalize() {
    float scale_aspect_x = 0.9f * (size_.x / message_.getLocalBounds().width);
    float scale_aspect_y = 0.9f * (size_.y / message_.getLocalBounds().height);
    float scale_aspect = std::min(1.f, std::min(scale_aspect_x, scale_aspect_y));
    message_.setScale(scale_aspect, scale_aspect);
}
