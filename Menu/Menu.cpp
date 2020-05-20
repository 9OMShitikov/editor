
#include "Menu.h"
FileMenu::FileMenu(sf::RenderWindow* window, float x, float y, sf::Vector2f size) :
        size_(size),
        window_(window),
        entries_(std::vector<MenuEntry>(3)) {
    if (!font_.loadFromFile("arial.ttf")) {
        throw std::logic_error("Cannot load font in Menu");
    }

    for (int i = 0; i < entries_.size(); ++i) {
        entries_[i].entry.setPosition(x, y + size.y / entries_.size() * float(i));
        entries_[i].entry.setSize(sf::Vector2f(size.x, size.y/entries_.size()));
        entries_[i].entry.setFillColor(sf::Color::Blue);
        entries_[i].entry.setOutlineColor(sf::Color::White);
        entries_[i].entry.setOutlineThickness(3);

        entries_[i].name.setFillColor(sf::Color::Yellow);
        entries_[i].name.setFont(font_);
        entries_[i].name.setCharacterSize(17);
        entries_[i].name.setPosition(entries_[i].entry.getPosition().x + 5,
                                     entries_[i].entry.getPosition().y +
                                     entries_[i].entry.getSize().y / 2 -
                                     entries_[i].name.getLocalBounds().height / 2 - 10);
    }

    entries_[0].name.setString("Save");
    entries_[1].name.setString("Save as...");
    entries_[2].name.setString("Load");

    entries_[0].type = MenuEntryType::Save;
    entries_[1].type = MenuEntryType::SaveAs;
    entries_[2].type = MenuEntryType::Load;
}

bool FileMenu::HasResult() const{
    return has_result_;
}

void FileMenu::SetResult(MenuEntryType result) {
    if (!has_result_) {
        has_result_ = true;
        result_ = result;
    }
}

MenuEntryType FileMenu::GetResult() const {
    return result_;
}

void FileMenu::ProcessEvent(sf::Event event) {
    sf::Vector2f mouse_coordinats (sf::Mouse::getPosition(*window_));

    if (event.type == sf::Event::MouseButtonPressed) {
        if (initial_press_) {
            initial_press_ = false;
            return;
        }
        for (int i = 0; i < entries_.size(); ++i) {
            if (entries_[i].entry.getGlobalBounds().contains(mouse_coordinats)) {
                SetResult(entries_[i].type);
            }
        }
        if (!has_result_) {
            SetResult(MenuEntryType::Empty);
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        int new_active_position = -1;
        for (int i = 0; i < entries_.size(); ++i) {
            if (entries_[i].entry.getGlobalBounds().contains(mouse_coordinats)) {
                new_active_position = i;
            }
        }
        if (active_position_ != new_active_position) {
            if (active_position_ != -1) {
                entries_[active_position_].entry.setFillColor(sf::Color::Blue);
            }
            if (new_active_position != -1) {
                entries_[new_active_position].entry.setFillColor(sf::Color::Red);
            }

            active_position_ = new_active_position;
        }
    }
}

void FileMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (int i = 0; i < entries_.size(); ++i) {
        target.draw(entries_[i].entry);
    }
    for (int i = 0; i < entries_.size(); ++i) {
        target.draw(entries_[i].name);
    }
}