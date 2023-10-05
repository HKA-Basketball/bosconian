#ifndef BOSCONIAN_SETTINGS_H
#define BOSCONIAN_SETTINGS_H

// Coinage options for gameplay
enum class Coinage {
    One_One = 0, // Norm
    One_Two,
    One_Three,
    Two_One,
    Two_Three,
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
enum class Lives : unsigned int {
    One = 1,
    Two = 2,
    Three = 3, // Norm
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
    Coinage coinage = Coinage::One_One;
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

    PlayOptions playOptions;
    bool debugMode = false;
    bool customLevel = false;

    Settings() {}
    ~Settings() {}

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

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

    void setSWA(int state);

    void setSWB(int state);

    int getSWA() const;

    int getSWB() const;

    bool getDebugMode() {
        return debugMode;
    }

    void setDebugMode(bool isDebugModeOn) {
        debugMode = isDebugModeOn;
    }

    bool getCustomLevelMode() {
        return customLevel;
    }

    void setCustomLevelMode(bool isCustomLevelOn) {
        customLevel = isCustomLevelOn;
    }

    unsigned int getStartLives() {
        return static_cast<unsigned int>(playOptions.lives);
    }

private:
    Lives getLivesFromBits(int bits);
    int getBitsFromLives(Lives lives) const;
};


#endif //BOSCONIAN_SETTINGS_H
