#ifndef BOSCONIAN_RENDERENGINE_H
#define BOSCONIAN_RENDERENGINE_H

#pragma once

#include <array>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Graphic/Sprite.h"
#include "../Graphic/Fonts.h"
#include "../Graphic/TextAlign.h"

#include "../Model/Menus/Items/MenuItem.h"
#include "../Model/Menus/Items/SwitchItem.h"

#include "../Utilities/Config.h"
#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"

class RenderEngine {
private:
    SDL_Window* window;                             ///< The main window where rendering is performed.
    SDL_Renderer* renderer;                         ///< The main renderer.
    SDL_Texture* spritesheet;                       ///< Spritesheet containing game images.
    std::array<TTF_Font*, Font::Type::MAX> fonts;   ///< Array of fonts used in the game.

    int width{Config::windowWidth};     ///< Width of the rendering window.
    int height{Config::windowHeight};   ///< Height of the rendering window.


    /**
     * @brief Initializes SDL and its subsystems.
     */
    void InitializeSDL();

    /**
     * @brief Cleans up SDL resources and subsystems.
     */
    void CleanupSDL();

    /**
     * @brief Loads the main spritesheet.
     */
    void loadSpritesheet();

    /**
     * @brief Unloads the main spritesheet.
     */
    void unloadSpritesheet();

    /**
     * @brief Loads game fonts.
     */
    void loadFonts();

    /**
     * @brief Unloads game fonts.
     */
    void unloadFonts();

public:
    /**
     * @brief Constructor that initializes the render engine.
     */
    RenderEngine();

    /**
     * @brief Destructor that cleans up resources.
     */
    ~RenderEngine();

    /**
     * @brief Begins the rendering scene by setting up the initial render state.
     */
    void beginScene();

    /**
     * @brief Completes the rendering process for the current frame, presenting it on the screen.
     */
    void endScene();

    /**
     * @brief Renders a line on the screen.
     * @param start Start position of the line.
     * @param end End position of the line.
     * @param color Color of the line.
     */
    void renderLine(const Vector2D &start, const Vector2D &end, const SDL_Color &color) const;

    /**
     * @brief Renders a cone shape (using 3 points) on the screen.
     * @param start Start position of the cone.
     * @param apex Apex position of the cone.
     * @param end End position of the cone.
     * @param color Color of the cone.
     */
    void renderCone(const Vector2D &start, const Vector2D &apex, const Vector2D &end, const SDL_Color &color) const;

    /**
     * @brief Renders a rectangle on the screen.
     * @param position Top-left position of the rectangle.
     * @param size Size of the rectangle.
     * @param color Color of the rectangle.
     * @param filled If true, the rectangle will be filled; otherwise, it will be outlined.
     */
    void renderRectangle(const Vector2D &position, const Vector2D &size, const SDL_Color &color, bool filled = false) const;

    /**
     * @brief Renders a rotated rectangle on the screen.
     * @param position Center position of the rectangle.
     * @param size Size of the rectangle.
     * @param angle Rotation angle of the rectangle.
     * @param color Color of the rectangle.
     */
    void renderRotatedRectangle(const Vector2D &position, const Vector2D &size, const Degree &angle, const SDL_Color& color) const;

    /**
     * @brief Renders a sprite on the screen.
     * @param sprite Reference to the sprite to be rendered.
     * @param angle Rotation angle for the sprite.
     * @param centered If true, the sprite will be rendered based on its center.
     * @param centered How much the sprite should be scaled.
     * @param center Custom center point for the sprite rotation (if provided).
     * @param flip Flip configuration for the sprite.
     */
    void renderSprite(Sprite& sprite, float angle = 0.0, bool centered = false, float scale = 1.0f, SDL_FPoint* center = nullptr,
                      SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    /**
     * @brief Renders text on the screen.
     * @param text Text to be rendered.
     * @param position Position of the text.
     * @param color Color of the text.
     * @param fontIndex Font index to be used for the text rendering.
     * @param align Text alignment relative to the provided position.
     */
    void renderText(const std::string& text, const Vector2D& position, const SDL_Color& color = Config::ColorWhite,
                    const uint32_t& fontIndex = Font::JOYSTIX_38PX, TextAlign align = TextAlign::LEFT) const;

    /**
     * @brief Renders a menu item on the screen.
     * @param menuItem Reference to the menu item to be rendered.
     * @param color Color of the menu item.
     * @param fontIndex Font index to be used for the menu item rendering.
     */
    void renderMenuItem(const MenuItem& menuItem, const SDL_Color& color = Config::ColorWhite,
                        const uint32_t& fontIndex = Font::JOYSTIX_38PX) const;

    /**
     * @brief Renders a switch item on the screen.
     * @param switchItem Reference to the switch item to be rendered.
     * @param color Background color of the switch.
     * @param textColor Text color of the switch.
     * @param fontIndex Font index to be used for the switch item rendering.
     */
    void renderSwitchItem(const SwitchItem &switchItem, const SDL_Color &color, const SDL_Color &textColor = Config::ColorWhite,
                          const uint32_t &fontIndex = Font::JOYSTIX_38PX) const;


};

#endif //BOSCONIAN_RENDERENGINE_H
