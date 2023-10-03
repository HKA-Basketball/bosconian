#ifndef BOSCONIAN_LEVELEDITORSTATE_H
#define BOSCONIAN_LEVELEDITORSTATE_H

#include "State.h"

class LevelEditorState : public State {
public:
    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};


#endif //BOSCONIAN_LEVELEDITORSTATE_H
