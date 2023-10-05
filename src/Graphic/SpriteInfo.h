#ifndef BOSCONIAN_SPRITEINFO_H
#define BOSCONIAN_SPRITEINFO_H

#include <map>
#include "SDL.h"

enum class SpriteInfo {
    EXPLOSION_01 = 0,
    EXPLOSION_02,
    EXPLOSION_03,
    BOMB,
    ASTEROID_01,
    ASTEROID_02,
    ASTEROID_03,
    CANON_L,
    CANON_L_DOWN,
    CANON_L_DOWN_NORM,
    CANON_L_UP,
    CANON_L_UP_NORM,
    CANON_L_NORM,
    CANON_R,
    CANON_R_DOWN,
    CANON_R_DOWN_NORM,
    CANON_R_UP,
    CANON_R_UP_NORM,
    CANON_R_NORM,
    CORE,
    E_TYPE,
    I_TYPE_ATTACK,
    I_TYPE_NORM,
    P_TYPE_ATTACK,
    P_TYPE_NORM,
    PLAYER,
    SPY,
    PROJECTILE
};

const std::map<SpriteInfo, SDL_Rect> spriteMap = {
        {SpriteInfo::EXPLOSION_01,      {416, 0,   56,  60}},
        {SpriteInfo::EXPLOSION_02,      {0,   60,  64,  60}},
        {SpriteInfo::EXPLOSION_03,      {124, 60,  64,  64}},
        {SpriteInfo::ASTEROID_01,       {48,  0,   56,  44}},
        {SpriteInfo::ASTEROID_02,       {0,   0,   48,  40}},
        {SpriteInfo::ASTEROID_03,       {104, 0,   52,  44}},
        {SpriteInfo::CANON_L,           {0,   220, 64,  64}},
        {SpriteInfo::CANON_L_DOWN,      {36,  284, 92,  96}},
        {SpriteInfo::CANON_L_DOWN_NORM, {36,  540, 92,  96}},
        {SpriteInfo::CANON_L_UP,        {36,  124, 92,  96}},
        {SpriteInfo::CANON_L_UP_NORM,   {36,  380, 92,  96}},
        {SpriteInfo::CANON_L_NORM,      {0,   476, 64,  64}},
        {SpriteInfo::CANON_R,           {225, 221, 64,  64}},
        {SpriteInfo::CANON_R_DOWN,      {160, 284, 92,  96}},
        {SpriteInfo::CANON_R_DOWN_NORM, {160, 540, 92,  96}},
        {SpriteInfo::CANON_R_UP,        {160, 124, 92,  96}},
        {SpriteInfo::CANON_R_UP_NORM,   {160, 380, 92,  96}},
        {SpriteInfo::CANON_R_NORM,      {225, 477, 64,  64}},
        {SpriteInfo::CORE,              {64,  220, 160, 64}},
        {SpriteInfo::BOMB,              {64,  60,  60,  60}},
        {SpriteInfo::E_TYPE,            {188, 60,  28,  64}},
        {SpriteInfo::I_TYPE_ATTACK,     {304, 0,   56,  56}},
        {SpriteInfo::I_TYPE_NORM,       {360, 0,   56,  56}},
        {SpriteInfo::P_TYPE_ATTACK,     {156, 0,   52,  48}},
        {SpriteInfo::P_TYPE_NORM,       {208, 0,   52,  48}},
        {SpriteInfo::PLAYER,            {216, 60,  60,  64}},
        {SpriteInfo::SPY,               {260, 0,   44,  52}},
        {SpriteInfo::PROJECTILE,        {276, 60,  8,   8}}
};


#endif //BOSCONIAN_SPRITEINFO_H
