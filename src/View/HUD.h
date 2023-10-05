#ifndef BOSCONIAN_HUD_H
#define BOSCONIAN_HUD_H

#include <SDL.h>
#include "RenderEngine.h"
#include "../Utilities/Config.h"
#include "../Model/GameModel.h"
#include "../Graphic/Sprite.h"

class HUD {
    RenderEngine* renderEngine;
    GameModel* gameModel;

public:
    HUD(RenderEngine* renderEngine, GameModel* gameModel) : renderEngine(renderEngine), gameModel(gameModel) {}

    void render() {
        renderBackground();
        renderScore();
        renderCondition();
        renderRadar();
        renderLives();
        renderRound();
    }

private:

    void renderBackground() {
        renderEngine->renderRectangle(
                {Config::screenWidth, 0},
                {Config::HUDWidth, Config::screenHeight},
                Config::ColorBlack,
                true);
    }

    void renderScore() {
        unsigned int points = gameModel->getScore();
        unsigned int highscore = gameModel->getHighscore();

        renderEngine->renderText("Hi-score", {Config::windowWidth, 0},
                                 Config::ColorRed, Font::JOYSTIX_38PX, TextAlign::RIGHT);
        renderEngine->renderText(std::to_string(highscore), {Config::windowWidth, 38},
                                 Config::ColorWhite, Font::JOYSTIX_38PX, TextAlign::RIGHT);

        renderEngine->renderText("Score", {Config::windowWidth, 38*2},
                                 Config::ColorWhite, Font::JOYSTIX_38PX, TextAlign::RIGHT);
        renderEngine->renderText(std::to_string(points), {Config::windowWidth, 38*3},
                                 Config::ColorWhite, Font::JOYSTIX_38PX, TextAlign::RIGHT);
    }

    void renderCondition() {

        auto conditionColor = Config::ColorGreen;
        std::string conditionText = "Green";
        auto textSize = Font::JOYSTIX_38PX;

        if(gameModel->getCondition() == Condition::YELLOW) {
            conditionColor = Config::ColorYellow;
            conditionText = "Yellow";

        } else if (gameModel->getCondition() == Condition::RED) {
            conditionColor = Config::ColorRed;
            conditionText = "Red !!";

        } else if (gameModel->getCondition() == Condition::FORMATION_ATTACK) {
            conditionColor = Config::ColorRed;
            conditionText = "Formation Attack";
            textSize = Font::JOYSTIX_24PX;
        }

        renderEngine->renderRectangle({Config::screenWidth, 38*4+1}, {Config::HUDWidth, 100},
                                      conditionColor, true);

        renderEngine->renderText(conditionText, {Config::screenWidth + (Config::HUDWidth/2), 38*4+1+50},
                                 Config::ColorBlack, textSize, TextAlign::CENTER);
    }

    void renderRadar() {
        renderEngine->renderRectangle(
                {Config::screenWidth, Config::HUDVerticalOffset},
                {Config::HUDWidth, Config::HUDHeight},
                Config::ColorViolet,
                true);

        for (Base* base : *gameModel->getBases()) {
            Vector2D scaledBasePosition = scalePositionToMapSize(base->getPosition());
            renderEngine->renderRectangle(scaledBasePosition, {8, 8}, Config::ColorGreen, true);
        }

        Vector2D scaledPlayerPosition = scalePositionToMapSize(gameModel->getPlayer()->getPosition());
        renderEngine->renderRectangle(scaledPlayerPosition, {8, 8}, Config::ColorWhite, true);
    }

    void renderLives() {
        Sprite playerSprite(SpriteInfo::PLAYER);

        for (int i = 0; i < gameModel->getLives(); ++i) {
            int positionX = Config::screenWidth + (i * (Config::liveSpriteWidth + 4));
            playerSprite.setPosition({static_cast<float>(positionX), Config::livesVerticalOffset});
            playerSprite.setSize({Config::liveSpriteWidth, Config::liveSpriteHeight});
            renderEngine->renderSprite(playerSprite, 0);
        }
    }

    void renderRound() {
        unsigned int round = gameModel->getRound();

        renderEngine->renderText("Round", {Config::screenWidth, Config::windowHeight-38},
                                             Config::ColorWhite, Font::JOYSTIX_38PX, TextAlign::LEFT);
        renderEngine->renderText(std::to_string(round), {Config::windowWidth, Config::windowHeight-38},
                                             Config::ColorWhite, Font::JOYSTIX_38PX, TextAlign::RIGHT);
    }

    Vector2D scalePositionToMapSize(const Vector2D& position) {
        int scaledX = Config::screenWidth + ((position.x / Config::levelWidth) * (Config::HUDWidth - 8));
        int scaledY = Config::HUDVerticalOffset + ((position.y / Config::levelHeight) * (Config::HUDHeight - 8));

        return Vector2D(scaledX, scaledY);
    }
};


#endif //BOSCONIAN_HUD_H
