#ifndef BOSCONIAN_GAMECONTROLLER_H
#define BOSCONIAN_GAMECONTROLLER_H

#include "../Model/GameModel.h"
#include "../View/RenderEngine.h"
#include "../Controller/InputHandler.h"
#include "../States/StateMachine.h"
#include "../Utilities/FrameTimer.h"
#include "../Utilities/Settings.h"
#include "../Sound/SoundEngine.h"

class GameController {
    RenderEngine* renderEngine;
    SoundEngine* soundEngine;

    InputHandler* inputHandler;

    StateMachine* stateMachine;

    FrameTimer* frameTimer;

public:
    GameController() {
        renderEngine = new RenderEngine();

        soundEngine = new SoundEngine();
        soundEngine->startBackgroundMusic("sounds/loop.wav");

        inputHandler = new InputHandler();

        stateMachine = StateMachine::InitInstance(renderEngine, soundEngine, inputHandler);

        frameTimer = new FrameTimer(60);
    }

    ~GameController() {
        soundEngine->stopBackgroundMusic();
        StateMachine::DestroyInstance();
        Settings::DestroyInstance();

        delete renderEngine;
        delete soundEngine;
        delete inputHandler;
        delete frameTimer;
    }

    void start() {
        while(!inputHandler->hasQuit()) loop();
    }

private:
    void loop() {

        frameTimer->startFrame();

        inputHandler->update();

        stateMachine->getCurrentState()->handleInput(frameTimer->getDeltaTime());

        stateMachine->getCurrentState()->update(frameTimer->getDeltaTime());

        renderEngine->beginScene();

        stateMachine->getCurrentState()->render();

        renderEngine->endScene();

        frameTimer->delayFrame();
    }

};


#endif //BOSCONIAN_GAMECONTROLLER_H
