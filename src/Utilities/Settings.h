#ifndef BOSCONIAN_SETTINGS_H
#define BOSCONIAN_SETTINGS_H

// Coinage options for gameplay
enum class Coinage {
    One_One = 0, // Norm
    One_Tow,
    One_Three,
    Tow_One,
    Tow_Three,
    Three_One,
    Four_One,
    Free_Play
};

// Bonus fighter options for gameplay
enum class BonusFighter {
    // if Lives not set to 5
    //20K and 70K Only
    Opt0_0 = 0,
    //15K and 50K Only
    Opt0_1,
    //30K, 100K, Every 100K
    Opt0_2,
    //20K, 70K, Every 70K
    Opt0_3, // Norm
    //15K, 70K, Every 70K
    Opt0_4,
    //15K, 50K, Every 50K
    Opt0_5,
    //10K, 50K, Every 50K
    Opt0_6,
    None,

    // if Lives set to 5
    //30K, 120K, Every 120K
    Opt1_0,
    //30K, 100K, Every 100K
    Opt1_1,
    //30K, 80K, Every 80K
    Opt1_2,
    //30K and 120K Only
    Opt1_3, // Norm
    //20K and 100K Only
    Opt1_4,
    //20K and 70K Only
    Opt1_5,
    //15K and 70K Only
    Opt1_6,
    None_pl
};

// Starting lives options
enum class Lives {
    On = 1,
    Tow,
    Three, // Norm
    Five = 5
};

// Difficulty options
enum class Difficulty {
    Medium = 0, // Norm
    Hardest,
    Easy,
    Auto
};

// Cabinet type options
enum class Cabinet {
    Cocktail = 0,
    Upright // Norm & Only Supported
};

struct PlayOptions {
    // Gameplay settings
    Coinage conage = Coinage::One_One;
    BonusFighter bonusFighter = BonusFighter::Opt0_3;
    Lives lives = Lives::Three;
    Difficulty difficulty = Difficulty::Medium;
    bool allowContinue = true;
    bool demoSound = true;
    bool freeze = false;
    Cabinet cabinet = Cabinet::Upright;
};

class Settings {
    static Settings* instance;

    Settings() {}
    ~Settings() {}

public:
    static Settings* Instance() {
        if (!instance) {
            instance = new Settings();
            return instance;
        }
        return instance;
    }

    static void DestroyInstance() {
        delete instance;
        instance = nullptr;
    }

    void setSWA(int state) {
        // Update lives based on swa_6 and swa_7
        playOptions.lives = GetLivesFromBits((state >> 6) & 0x03);

        // Update conage based on swa_0, swa_1, and swa_2
        playOptions.conage = static_cast<Coinage>((state >> 0) & 0x07);

        // Update bonusFighter based on swa_3 to swa_5 and lives
        if (playOptions.lives != Lives::Five) {
            playOptions.bonusFighter = static_cast<BonusFighter>((state >> 3) & 0x07);
        } else {
            playOptions.bonusFighter = static_cast<BonusFighter>(8 + ((state >> 3) & 0x07));
        }
    }

    void setSWB(int state) {
        playOptions.difficulty = static_cast<Difficulty>((state >> 1) & 0x01 | state & 0x01);

        playOptions.allowContinue = (state >> 2) & 0x01;
        playOptions.demoSound = (state >> 3) & 0x01;
        playOptions.freeze = (state >> 4) & 0x01;
        playOptions.cabinet = static_cast<Cabinet>((state >> 7) & 0x01);
    }

    int getSWA() const {
        int state = 0;

        // Get lives as bits from playOptions.lives
        state |= GetBitsFromLives(playOptions.lives) << 6;

        // Get conage as bits from playOptions.conage
        state |= (static_cast<int>(playOptions.conage) & 0x07) << 0;

        // Get bonusFighter as bits based on playOptions.lives
        if (playOptions.lives != Lives::Five) {
            state |= (static_cast<int>(playOptions.bonusFighter) & 0x07) << 3;
        } else {
            state |= ((static_cast<int>(playOptions.bonusFighter) - 8) & 0x07) << 3;
        }

        return state;
    }

    int getSWB() const {
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

    bool getDebugMode() {
        return debugMode;
    }

    void setDebugMode(bool isDebugModeOn) {
        debugMode = isDebugModeOn;
    }

private:
    PlayOptions playOptions;
    bool debugMode = false;

    Lives GetLivesFromBits(int bits) {
        switch (bits) {
            case 0b00: return Lives::Five;
            case 0b11: return Lives::On;
            case 0b10: return Lives::Tow;
            case 0b01: return Lives::Three;
            default: return Lives::Three; // Default to Three
        }
    }

    int GetBitsFromLives(Lives lives) const {
        switch (lives) {
            case Lives::Five: return 0b00;
            case Lives::On: return 0b11;
            case Lives::Tow: return 0b10;
            case Lives::Three: return 0b01;
            default: return 0b01; // Default to Three
        }
    }
};


#endif //BOSCONIAN_SETTINGS_H
