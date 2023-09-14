#ifndef BOSCONIAN_BEHAVIOUR_H
#define BOSCONIAN_BEHAVIOUR_H

#include "../EntityModel.h"
#include "../EntityView.h"
#include "../../Projectile.h"
#include "../../../Sound/SoundManager.h"
#include "../../../Physics/Collision.h"
#include "../../../Physics/Hitbox.h"
#include "../../../Drawing/Texture.h"
#include "../../../../includes.h"

namespace Game {

    class Behavior {
    public:
        virtual void update(EntityModel &model, float deltaTime = 0.f) = 0;

        virtual void update(EntityView &view, float deltaTime = 0.f) = 0;
    };

}

#endif //BOSCONIAN_BEHAVIOUR_H
