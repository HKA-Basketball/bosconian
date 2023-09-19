#ifndef BOSCONIAN_ANIMATION_H
#define BOSCONIAN_ANIMATION_H

#include "../../Drawing/Texture.h"
#include "../../../includes.h"

class Animation {
protected:
    bool animationStart{false};
    bool animationEnd{false};
    float animationTime{0.f};
    const float animationDuration{250.f};

    std::vector<std::string> images{};

public:

    Animation() {}

    void startAnimation() {
        animationStart = true;
        animationTime = 0.f;
    }

    void update(std::shared_ptr<Drawing::Texture> texture, float deltaTime);

    bool hasStarted() {
        return animationStart;
    }

    bool hasEnded() {
        return animationEnd;
    }

};


#endif //BOSCONIAN_ANIMATION_H
