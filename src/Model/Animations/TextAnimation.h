#ifndef BOSCONIAN_TEXTANIMATION_H
#define BOSCONIAN_TEXTANIMATION_H

#include <string>
#include <iostream>
#include <utility>

#include "Animation.h"

class TextAnimation : public Animation {
    std::string text;
    float elapsedTime{0.f};
    float length{3.f};

public:
    explicit TextAnimation(std::string text) : Animation(), text(std::move(text)) {}

    void start() override {
        elapsedTime = 0;
        Animation::start();
    }

    void update(float deltaTime) override {
        if (!isPlaying) {
            return;
        }

        elapsedTime += deltaTime;
        if (elapsedTime >= length) {
            isPlaying = false;
        }
    }

    std::string getText() const {
        return text;
    }

};

#endif //BOSCONIAN_TEXTANIMATION_H
