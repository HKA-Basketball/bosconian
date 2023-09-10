#ifndef BOSCONIAN_HUD_H
#define BOSCONIAN_HUD_H

#include "../Model/GameSession.h"
#include "../Model/Entity/Player.h"

class HUD {
public:
    HUD(const Player& player, const GameSession& session);
    ~HUD() = default;

    void Render(SDL_Renderer* renderer);

private:
    const Player& player;
    const GameSession& gameSession;

    // Add other member variables for textures or surfaces here if necessary
};


#endif //BOSCONIAN_HUD_H
