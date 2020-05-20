#ifndef LEVELGENERATOR_MOUSESTATUS_H
#define LEVELGENERATOR_MOUSESTATUS_H

#include "../GeomObjects/Button.h"

class MouseStatus {
public:

    static TextureName getLandscape() {
        assert(landscape != nullptr);
        return landscape->getTextureName();
    }

    static LandscapeButton* getLandscapeButton() {
        return landscape;
    }

    static void setLandscapeButton(LandscapeButton* button) {
        assert(landscape != button);
        if (button!= nullptr && landscape != nullptr) {
            landscape->click();
        }
        assert(button == nullptr || landscape == nullptr);
        landscape = button;
    }

    static void setPressedStatus(bool is_pressed) {
        is_pressed_ = is_pressed;
    }

    static bool getPressedStatus() {
        return is_pressed_;
    }

private:
    static LandscapeButton* landscape;
    static bool is_pressed_;
};


#endif //LEVELGENERATOR_MOUSESTATUS_H
