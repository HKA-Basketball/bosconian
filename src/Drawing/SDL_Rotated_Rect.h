#ifndef BOSCONIAN_SDL_ROTATED_RECT_H
#define BOSCONIAN_SDL_ROTATED_RECT_H

namespace Drawing {

    struct SDL_Rotated_Rect {
        int x, y;
        int w, h;
        double angle;
    };
}

#endif //BOSCONIAN_SDL_ROTATED_RECT_H
