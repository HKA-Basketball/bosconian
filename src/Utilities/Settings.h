#ifndef BOSCONIAN_SETTINGS_H
#define BOSCONIAN_SETTINGS_H

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

    void setSWA(int state) {

    }

    void setSWB(int state) {

    }
};


#endif //BOSCONIAN_SETTINGS_H
