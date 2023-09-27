#ifndef BOSCONIAN_GAMEVIEW_H
#define BOSCONIAN_GAMEVIEW_H

#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"

class GameView {
    static GameView* instance;

    GameView() = default;
    ~GameView() = default;

public:
    static GameView* Instance() {
        if (!instance) {
            instance = new GameView();
            return instance;
        }
        return instance;
    }


    bool drawBackground();

    void drawHitbox();

    //void drawCannonHitbox();

    void render(float deltaTime);

    void drawPlayer();
};

#endif //BOSCONIAN_GAMEVIEW_H
