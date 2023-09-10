#include "HUD.h"
#include <SDL.h>
#include <SDL_ttf.h>

HUD::HUD(const Player& p, const GameSession& session)
        : player(p), gameSession(session) {}

void HUD::Render(SDL_Renderer* renderer) {
    // For simplicity, just showing text rendering for lives and score
    // In a full implementation, you'd want more visual elements, possibly using SDL_ttf or another text rendering approach

    char buffer[100];

    // Display player's lives
    //sprintf(buffer, "Lives: %d", player.GetLives());

    //SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, buffer, color);
    //SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 10;
    Message_rect.y = 10;
    Message_rect.w = 100;
    Message_rect.h = 40;

    //SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Display score
    //sprintf(buffer, "Score: %d", gameSession.GetScore());
    // Similar rendering logic as above...

    // Clean up surfaces and textures
    //SDL_FreeSurface(surfaceMessage);
    //SDL_DestroyTexture(Message);

    // ... repeat for other HUD elements
}
