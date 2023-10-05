#include "TextAnimation.h"

TextAnimation::TextAnimation(std::string text) : Animation(), text(std::move(text)) {}

void TextAnimation::start() {
    elapsedTime = 0;
    Animation::start();
}

void TextAnimation::update(float deltaTime) {
    if (!isPlaying) {
        return;
    }

    elapsedTime += deltaTime;
    if (elapsedTime >= length) {
        isPlaying = false;
    }
}

std::string TextAnimation::getText() const {
    return text;
}
