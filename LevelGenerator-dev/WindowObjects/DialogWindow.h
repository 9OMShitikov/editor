#ifndef LEVELGENERATOR_DIALOGWINDOW_H
#define LEVELGENERATOR_DIALOGWINDOW_H

#include "SFML/Graphics.hpp"
#include "../Managers/EventManager.h"

class DialogWindow : public sf::RenderWindow {
public:
    explicit DialogWindow(std::string&& message, std::string* user_response, EventManager* click_manager = nullptr);

    DialogWindow(const DialogWindow& ) = delete;
    DialogWindow(DialogWindow&& ) = delete;
    DialogWindow& operator=(const DialogWindow& ) = delete;
    DialogWindow& operator=(DialogWindow&& ) = delete;
    ~DialogWindow() override;

    void EnterPressed(InputBox*);
    void run();

private:

    void alignWindow();
    void queryConstructor(std::string&& query_text);
    void alignQuery();
    void fontSizeNormalize();
    void alignResponse();

    bool close_window_ = false;
    bool init_click_manager_ = false;

    const sf::Vector2u size_;
    sf::Font font_;
    sf::Text query_;
    InputBox message_box_;
    std::string* user_response_;
    EventManager* click_manager_;
};


#endif //LEVELGENERATOR_DIALOGWINDOW_H