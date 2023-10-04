#include <iostream>

#include "src/Controller/GameController.h"

int main(int argc, char* args[]) {

    auto* controller = new GameController();
    controller->start();
    delete controller;

    return 0;
}
