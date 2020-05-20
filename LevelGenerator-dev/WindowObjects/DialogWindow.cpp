#include "DialogWindow.h"

DialogWindow::DialogWindow(std::string&& message, std::string* user_response, EventManager *click_manager):
        sf::RenderWindow(sf::VideoMode(600, 200),"Dialog window",
                sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(0, 0, 8)),
        size_(sf::Vector2u(600, 200)),
        init_click_manager_(click_manager == nullptr),
        click_manager_(init_click_manager_ ? new EventManager() : click_manager),
        user_response_(user_response),
        message_box_(this) {

    if (!font_.loadFromFile("arial.ttf")) {
        throw std::runtime_error("It is not possible to load the font");
    }
    alignWindow();
    queryConstructor(std::move(message));
    alignResponse();

    click_manager_->addWindowObj(&message_box_, this);
}

DialogWindow::~DialogWindow() {
    if (init_click_manager_) {
        delete click_manager_;
    }
}

void DialogWindow::EnterPressed(InputBox* box) {
    *user_response_ = std::move(box->getUserText());
    if (!user_response_->empty()) {
        close_window_ = true;
    }
}

void DialogWindow::run() {
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

        draw(query_);
        draw(message_box_);
        display();
    }
}

void DialogWindow::alignWindow() {
    size_t x_centre = (sf::VideoMode::getDesktopMode().width - size_.x) / 2;
    size_t y_centre = (sf::VideoMode::getDesktopMode().height - size_.y) / 2;
    setPosition(sf::Vector2i(x_centre, y_centre));
}

void DialogWindow::queryConstructor(std::string &&query_text) {
    query_.setFont(font_);
    query_.setString(query_text);
    query_.setFillColor(sf::Color::Black);
    query_.setCharacterSize(28);
    alignQuery();
    fontSizeNormalize();
}

void DialogWindow::alignQuery() {
    sf::FloatRect bounds = query_.getLocalBounds();
    sf::Vector2f query_centre = sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    query_.setOrigin(query_centre);
    sf::Vector2f query_pos = sf::Vector2f(static_cast<float>(size_.x) / 2, static_cast<float>(size_.y) / 3);
    query_.setPosition(query_pos);
}

void DialogWindow::fontSizeNormalize() {
    float scale_aspect_x = 0.9f * (size_.x / query_.getLocalBounds().width);
    float scale_aspect = std::min(1.f, scale_aspect_x);
    query_.setScale(scale_aspect, scale_aspect);
}

void DialogWindow::alignResponse() {
    sf::FloatRect bounds = message_box_.getLocalBounds();
    sf::Vector2f response_centre = sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    message_box_.setOrigin(response_centre);
    sf::Vector2f response_pos = sf::Vector2f(static_cast<float>(size_.x) / 2, static_cast<float>(size_.y) * 2 / 3);
    message_box_.setPosition(response_pos);
}
