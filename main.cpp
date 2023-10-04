#include <iostream>

#include "src/Model/GameModel.h"
#include "src/View/RenderEngine.h"
#include "src/Controller/InputHandler.h"
#include "src/Controller/GameController.h"
#include "src/States/StateMachine.h"
#include "src/Utilities/FrameTimer.h"
#include "src/Sound/SoundEngine.h"

int main(int argc, char* args[]) {

    auto* controller = new GameController();
    controller->start();
    delete controller;

    return 0;
}
