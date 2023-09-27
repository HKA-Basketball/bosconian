#ifndef BOSCONIAN_FONTS_H
#define BOSCONIAN_FONTS_H

#include <stdint-gcc.h>

namespace Font {
    enum Type : int
    {
        JOYSTIX_128PX = 0,
        JOYSTIX_64PX,
        JOYSTIX_38PX,
        JOYSTIX_24PX,
        JOYSTIX_16PX,
        // Space for more font options
        MAX // Maximum number of font options
    };
}

#endif //BOSCONIAN_FONTS_H
