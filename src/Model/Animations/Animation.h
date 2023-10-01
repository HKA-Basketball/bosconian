#ifndef BOSCONIAN_ANIMATION_H
#define BOSCONIAN_ANIMATION_H

class Animation {
protected:
    bool isPlaying{false}; // Whether the animation is currently playing

public:
    Animation() {}

    virtual void start() {
        isPlaying = true;
    }

    virtual void update(float deltaTime) = 0;

    virtual bool isDone() const {
        return !isPlaying;
    }
};

#endif //BOSCONIAN_ANIMATION_H
