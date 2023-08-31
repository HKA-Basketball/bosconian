#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include "SDL.h"
#include "Entity.h"

class Player : public Entity {
private:
    int lives;
    int score;
    // Any other player-specific attributes...

public:
    Player(SDL_Texture* texture);

    void Move(int dx, int dy);   // Function to move the player.
    void Shoot();                // Function to make the player shoot.

    virtual void Update() override;     // Update player's state.
    virtual void Render(SDL_Renderer* renderer) override;

    // Other player-specific functionalities...
};

#endif //BOSCONIAN_PLAYER_H
