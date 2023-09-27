#ifndef BOSCONIAN_HUD_H
#define BOSCONIAN_HUD_H

#include <SDL.h>
#include "RenderEngine.h"
#include "../Utilities/Config.h"
#include "../Model/GameModel.h"
#include "../Graphic/Sprite.h"

class HUD {
public:
    static void render() {
        renderBackground();
        renderRadar();
        renderLives();
    }

private:

    static void renderBackground() {
        RenderEngine::Instance()->renderRectangle(
                {Config::screenWidth, 0},
                {Config::HUDWidth, Config::screenHeight},
                Config::ColorBlack,
                true);
    }

    static void renderRadar() {
        RenderEngine::Instance()->renderRectangle(
                {Config::screenWidth, Config::HUDVerticalOffset},
                {Config::HUDWidth, Config::HUDHeight},
                Config::ColorViolet,
                true);

        for (Base* base : *GameModel::Instance()->getBases()) {
            Vector2D scaledBasePosition = scalePositionToMapSize(base->getPosition());
            RenderEngine::Instance()->renderRectangle(scaledBasePosition, {8, 8}, Config::ColorGreen, true);
        }

        Vector2D scaledPlayerPosition = scalePositionToMapSize(GameModel::Instance()->getPlayer()->getPosition());
        RenderEngine::Instance()->renderRectangle(scaledPlayerPosition, {8, 8}, Config::ColorWhite, true);
    }

    static void renderLives() {
        Sprite playerSprite(SpriteInfo::PLAYER);

        for (int i = 0; i < GameModel::Instance()->getLives(); ++i) {
            int positionX = Config::screenWidth + (i * (Config::liveSpriteWidth + 4));
            playerSprite.setPosition({static_cast<float>(positionX), Config::livesVerticalOffset});
            playerSprite.setSize({Config::liveSpriteWidth, Config::liveSpriteHeight});
            RenderEngine::Instance()->renderSprite(playerSprite, 0);
        }
    }

    static Vector2D scalePositionToMapSize(const Vector2D& position) {
        int scaledX = Config::screenWidth + ((position.x / Config::levelWidth) * (Config::HUDWidth - 8));
        int scaledY = Config::HUDVerticalOffset + ((position.y / Config::levelHeight) * (Config::HUDHeight - 8));

        return Vector2D(scaledX, scaledY);
    }
};


#endif //BOSCONIAN_HUD_H
