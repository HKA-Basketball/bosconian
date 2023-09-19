#ifndef BOSCONIAN_EXPLOSIONANIMATION_H
#define BOSCONIAN_EXPLOSIONANIMATION_H

#include "Animation.h"

class ExplosionAnimation : public Animation {
public:
    ExplosionAnimation() {
        Animation();
        images = {
            "astro-explo-01",
            "astro-explo-02",
            "astro-explo-03"
        };
    }
};

#endif //BOSCONIAN_EXPLOSIONANIMATION_H
