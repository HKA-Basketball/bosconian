#ifndef BOSCONIAN_NONMOVINGBEHAVIOUR_H
#define BOSCONIAN_NONMOVINGBEHAVIOUR_H

#include "Behaviour.h"
#include "../EntityView.h"
#include "../EntityModel.h"

namespace Game {

    class NonMovingBehavior : public Behavior {
    private:
        bool animationStart = false;
        bool animationEnd = false;
        float animationTime = 0.f;
        const float animationDuration = 250.f;
        std::vector<std::string> explosionImages = {
                "astro-explo-01",
                "astro-explo-02",
                "astro-explo-03"
        };

    public:
        void update(EntityModel &model, float deltaTime = 0.f) override {
            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
                animationTime = 0.f;
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
            }

            if (animationEnd)
                model.setActive(false);
        }

        void update(EntityView &view, float deltaTime = 0.f) override {
            if (!animationStart)
                return;

            animationTime += deltaTime * 1000.f;

            float progress = animationTime / animationDuration;
            progress = std::clamp(progress, 0.f, 1.f);
            int imageIndex = static_cast<int>(progress * (explosionImages.size() - 1));

            view.setTexture(explosionImages[imageIndex]);

            if (animationTime >= animationDuration)
                animationEnd = true;
        }
    };

}

#endif //BOSCONIAN_NONMOVINGBEHAVIOUR_H
