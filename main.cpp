#include <iostream>

#include "src/Model/GameModel.h"
#include "src/View/RenderEngine.h"
#include "src/Controller/InputHandler.h"
#include "src/States/StateMachine.h"
#include "src/Graphic/Fonts.h"
#include "src/Utilities/FrameTimer.h"
#include "src/Sound/SoundEngine.h"

int main(int argc, char* args[]) {

    auto* soundEngine = new SoundEngine();
    soundEngine->startBackgroundMusic("sounds/loop.wav");

    auto frameTimer = FrameTimer(60);

    while(true) {
        frameTimer.startFrame();

        InputHandler::Instance()->update();

        StateMachine::Instance()->getCurrentState()->handleInput(frameTimer.getDeltaTime());

        StateMachine::Instance()->getCurrentState()->update(frameTimer.getDeltaTime());

        RenderEngine::Instance()->beginScene();

        StateMachine::Instance()->getCurrentState()->render();

        RenderEngine::Instance()->endScene();

        frameTimer.delayFrame();
    }

    soundEngine->stopBackgroundMusic();
    delete soundEngine;

    return 0;
}
