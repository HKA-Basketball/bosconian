#ifndef BOSCONIAN_GAMECONTROLLER_H
#define BOSCONIAN_GAMECONTROLLER_H

#include "../View/RenderEngine.h"
#include "../Sound/SoundEngine.h"
#include "../Controller/InputHandler.h"
#include "../States/StateMachine.h"
#include "../Utilities/FrameTimer.h"
#include "../Utilities/Settings.h"

#include "../Model/GameModel.h"
#include "../Model/LevelEditorModel.h"
#include "../View/GameView.h"
#include "../View/LevelEditorView.h"

class GameController {
    RenderEngine* renderEngine;
    SoundEngine* soundEngine;
    InputHandler* inputHandler;
    StateMachine* stateMachine;

    FrameTimer* frameTimer;

    bool levelEditor{false};

    GameModel* gameModel{nullptr};
    GameView* gameView{nullptr};

    LevelEditorModel* levelEditorModel{nullptr};
    LevelEditorView* levelEditorView{nullptr};

public:
    GameController();
    ~GameController();

    void start();

private:
    void loop();
    void updateState();

};


#endif //BOSCONIAN_GAMECONTROLLER_H
