#ifndef LEVELGENERATOR_DIALOGLAYOUTFORM_H
#define LEVELGENERATOR_DIALOGLAYOUTFORM_H

#include <iostream>
#include <cstdarg>
#include "../GeomObjects/InputBox.h"
#include "../GeomObjects/Button.h"

class DialogLayoutForm {
public:

    explicit DialogLayoutForm(sf::Vector2f size):
        size_(size) {

        if (!font_.loadFromFile("arial.ttf")) {
            throw std::runtime_error("It is not possible to load the font");
        }
    };

    using DialogRow = std::vector<WindowObj*>;

    sf::Vector2f getSize() const {
        return size_;
    }

    std::vector<WindowObj*> getObjects() const {
        size_t row_cnt = dialog_rows_.size();

        float row_height = size_.y / (2 * static_cast<float>(row_cnt) + 1);
        float width_guard = size_.x / 12;
        float query_width = ((size_.x - 3 * width_guard) / 3) * 2;
        float response_width = (size_.x - 3 * width_guard) / 3;
        float message_width = size_.x - 2 * width_guard;

        std::cout << size_.x << " " << size_.y << std::endl;

        for (int i = 0; i < row_cnt; ++i) {
            float fist_obj_width = (dialog_rows_[i].size() == 1) ? message_width : query_width;

            dialog_rows_[i][0]->setPosition(width_guard, row_height * static_cast<float>(i) * 2 + row_height);
            dialog_rows_[i][0]->setSize(sf::Vector2f(fist_obj_width, row_height));

            float button_width = response_width / (2 * static_cast<float>(dialog_rows_[i].size() - 1) - 1);
            for (int j = 1; j < dialog_rows_[i].size(); ++j) {

                dialog_rows_[i][j]->setSize(sf::Vector2f(button_width, row_height));
                dialog_rows_[i][j]->setPosition(2 * width_guard + query_width + (static_cast<float>(j) - 1) * 2 * button_width,
                        row_height * static_cast<float>(i) * 2 + row_height);
            }
        }

        std::vector<WindowObj*> window_objects;
        for (const DialogRow& row : dialog_rows_) {
            for (auto window_obj_ptr : row) {
                window_objects.emplace_back(window_obj_ptr);
            }
        }

        return window_objects;
    };

    void addQuestion(std::string&& request_text, InputBox* response) {
        auto request = new InputBox(nullptr, InputBoxType::NonEditable, std::move(request_text));
        dialog_rows_.push_back({request, response});
    }

    void addChoiceQuestion(std::string&& question_text, int n, ...) {
        auto request = new InputBox(nullptr, InputBoxType::NonEditable, std::move(question_text));
        dialog_rows_.push_back({request});
        va_list args_list;
        va_start(args_list, n);
        for (int i = 0; i < n; ++i) {
            dialog_rows_.back().push_back(va_arg(args_list, Button*));
        }
        va_end(args_list);
    }

    void addWidget(WindowObj* widget) {
        dialog_rows_.push_back({widget});
    }

private:
    sf::Vector2f size_;
    sf::Font font_;
    std::vector<DialogRow> dialog_rows_;
};


#endif //LEVELGENERATOR_DIALOGLAYOUTFORM_H
