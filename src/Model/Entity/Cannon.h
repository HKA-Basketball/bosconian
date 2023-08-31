#ifndef BOSCONIAN_CANNON_H
#define BOSCONIAN_CANNON_H

#pragma once

enum class CannonState {
    ACTIVE,
    DESTROYED
};

class Cannon {
public:
    Cannon();
    ~Cannon() = default;

    CannonState GetState() const;
    void Destroy();

private:
    CannonState state;
};

#endif //BOSCONIAN_CANNON_H
