#include "Settings.h"

// Define the instance pointer
Settings* Settings::instance = nullptr;

void Settings::setSWA(int state) {
    // Update lives based on swa_6 and swa_7
    playOptions.lives = getLivesFromBits((state >> 6) & 0x03);

    // Update coinage based on swa_0, swa_1, and swa_2
    playOptions.coinage = static_cast<Coinage>((state >> 0) & 0x07);

    // Update bonusFighter based on swa_3 to swa_5 and lives
    if (playOptions.lives != Lives::Five) {
        playOptions.bonusFighter = static_cast<BonusFighter>((state >> 3) & 0x07);
    } else {
        playOptions.bonusFighter = static_cast<BonusFighter>(8 + ((state >> 3) & 0x07));
    }
}

void Settings::setSWB(int state) {
    playOptions.difficulty = static_cast<Difficulty>((state >> 1) & 0x01 | state & 0x01);

    playOptions.allowContinue = (state >> 2) & 0x01;
    playOptions.demoSound = (state >> 3) & 0x01;
    playOptions.freeze = (state >> 4) & 0x01;
    playOptions.cabinet = static_cast<Cabinet>((state >> 7) & 0x01);
}

int Settings::getSWA() const {
    int state = 0;

    // Get lives as bits from playOptions.lives
    state |= getBitsFromLives(playOptions.lives) << 6;

    // Get coinage as bits from playOptions.coinage
    state |= (static_cast<int>(playOptions.coinage) & 0x07) << 0;

    // Get bonusFighter as bits based on playOptions.lives
    if (playOptions.lives != Lives::Five) {
        state |= (static_cast<int>(playOptions.bonusFighter) & 0x07) << 3;
    } else {
        state |= ((static_cast<int>(playOptions.bonusFighter) - 8) & 0x07) << 3;
    }

    return state;
}

int Settings::getSWB() const {
    int state = 0;

    // Get difficulty and state bits from playOptions.difficulty
    state |= (static_cast<int>(playOptions.difficulty) & 0x01) << 1;
    state |= (static_cast<int>(playOptions.difficulty) & 0x01) << 0;

    // Get other state bits from playOptions
    state |= (static_cast<int>(playOptions.allowContinue) & 0x01) << 2;
    state |= (static_cast<int>(playOptions.demoSound) & 0x01) << 3;
    state |= (static_cast<int>(playOptions.freeze) & 0x01) << 4;
    state |= (static_cast<int>(playOptions.cabinet) & 0x01) << 7;

    return state;
}

Lives Settings::getLivesFromBits(int bits) {
    switch (bits) {
        case 0b00: return Lives::Five;
        case 0b11: return Lives::One;
        case 0b10: return Lives::Two;
        case 0b01: return Lives::Three;
        default: return Lives::Three; // Default to Three
    }
}

int Settings::getBitsFromLives(Lives lives) const {
    switch (lives) {
        case Lives::Five: return 0b00;
        case Lives::One: return 0b11;
        case Lives::Two: return 0b10;
        case Lives::Three: return 0b01;
        default: return 0b01; // Default to Three
    }
}