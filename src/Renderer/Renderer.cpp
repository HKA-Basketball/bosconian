#include "Renderer.h"
#include "../../Resources/fonts.h"

namespace Renderer {
    RendererSDL* g_renderer;

    RendererSDL::RendererSDL(Window *window, Uint32 flags) {
        renderer = SDL_CreateRenderer(window->sdl_HWND, -1, flags);

        if (!renderer) {
            LOG(std::string("Error: Could not create Renderer: ") + SDL_GetError());
            throw std::runtime_error("Failed to creat Renderer");
        }
        LOG(std::string("Renderer Successfully created"));

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        m_fonts.resize(FONT_MAX);

        if (!initSDL_TTF())
            throw std::runtime_error("Failed to init SDL_TTF");

        addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_38PX, 38);
        addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_16PX, 16);
        // More Fonts here

        LOG(std::string("Fonts Successfully loaded"));
    }

    bool RendererSDL::initSDL_TTF() {
        if (TTF_Init() < 0) {
            LOG(std::string("Error: intializing SDL_ttf: ") + TTF_GetError());
            return 0;
        }

        return 1;
    }

    bool RendererSDL::addFont(const void *mem, int size, int fontIndex, int fontPT) {
        SDL_RWops* pFontMem = SDL_RWFromConstMem(mem, size);

        if(!pFontMem)
        {
            LOG(std::string("Error: loading font Data: ") + TTF_GetError());
            return 0;
        }

        m_fonts[fontIndex] = TTF_OpenFontRW(pFontMem, 1, fontPT);

        if (!m_fonts[fontIndex])
        {
            LOG(std::string("Error: loading font index (") + std::to_string(fontIndex) + std::string("): ") + TTF_GetError());
            return 0;
        }

        return 1;
    }

    void RendererSDL::beginScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //SDL_DestroyTexture(texture);
    }

    void RendererSDL::endScene() {
        SDL_RenderPresent(renderer);
    }

    void RendererSDL::renderEntity(Game::Entity* entity, float deltaTime) {
        if (entity->isTriggerAnimation() && !entity->getAnimation()->hasStarted()) {
            Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
        }

        entity->getTexture()->draw();
        renderHitbox(entity->getHitbox(), entity->isActive());

        for (auto& projectile : entity->getProjectiles()) {
            renderProjectile(projectile);
        }
    }

   void RendererSDL::renderEntities(const std::vector<Game::Entity*>& entities, float deltaTime) {
       for (Game::Entity* entity : entities) {
            this->renderEntity(entity, deltaTime);
       }
    }

    void RendererSDL::renderHitbox(Physics::Hitbox* hitbox, bool active) {
        if (!Utils::GlobalVars::debugMode)
            return;

        Utils::Vector2D worldPos = hitbox->getPosition();
        Utils::Vector2D screenPos;
        Utils::render::WorldToScreen(worldPos, screenPos);

        SDL_Color color{
                static_cast<Uint8>(active ? 0 : 255),
                static_cast<Uint8>(active ? 255 : 0),
                0,
                255
        };

        if(!Utils::GlobalVars::collisionMode) {
            auto rect = (SDL_Rect) *hitbox;
            rect.x = static_cast<int>(screenPos.x);
            rect.y = static_cast<int>(screenPos.y);

            Drawing::g_drawing->rectangle(color, rect);

        } else {
            auto rotatedRect = (Drawing::SDL_Rotated_Rect) *hitbox;
            rotatedRect.x = static_cast<int>(screenPos.x);
            rotatedRect.y = static_cast<int>(screenPos.y);

            Drawing::g_drawing->rotatedRectangle(color, rotatedRect);
        }
    }

    void RendererSDL::renderProjectile(Game::Projectile* projectile) {
        // Render the projectile.

        Utils::Vector2D worldPos = Utils::Vector2D(projectile->getX(), projectile->getY());
        Utils::Vector2D screenPos;

        Utils::render::WorldToScreen(worldPos, screenPos);

        SDL_FRect rect = { screenPos.x, screenPos.y, (float)projectile->getWidth(), (float)projectile->getHeight() };
        Drawing::g_drawing->fillRectangleOutline({ 255, 255, 255, 255 }, rect);
    }

    void RendererSDL::renderBase(Game::BaseEntity* base, float deltaTime) {
        if (base->getSpy() && base->getSpy()->isActive())
            renderEntity(base->getSpy(), deltaTime);

        if (base->getEntities()[0]->isTriggerAnimation() && base->getEntities()[0]->isActive()) {
            renderEntity(base->getEntities()[0], deltaTime);
            return;
        }

        for (auto& entity : base->getEntities()) {
            renderEntity(entity, deltaTime);
        }
    }


} // Renderer