#ifndef BOSCONIAN_GRAPHICS_H
#define BOSCONIAN_GRAPHICS_H

#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <memory>
#include "SDL_Rotated_Rect.h"
#include "../../includes.h"

namespace Drawing {

    /**
     * \enum Alignment
     * \brief Enumeration representing text alignment.
     */
    enum : uint32_t {
        Left = 0,   // Left-aligned text
        Right,      // Right-aligned text
        Center      // Center-aligned text
    };

    /**
     * \class Graphics
     * \brief A class responsible for drawing graphics and managing textures.
     */
    class Graphics {
    private:
        const int MAX_CACHE_SIZE = 100; // Maximum size of the text cache

        /**
         * \struct TextCacheItem
         * \brief Structure for caching rendered text.
         */
        struct TextCacheItem {
            std::shared_ptr<SDL_Texture> texture; // Shared pointer to cached SDL_Texture
            int accessCount; // Counter to track cache access frequency
        };

        SDL_Renderer* g_renderer;
        //Caching
        std::map<std::string, SDL_Texture*> textures; // Map to store loaded textures
        std::map<std::string, TextCacheItem> textCache; // Map to store cached text textures
        std::list<std::string> accessQueue; // List to manage access order of text cache items

    public:
        /**
         * Constructor for the Graphics class.
         */
        Graphics();

        /**
         * Destructor for the Graphics class.
         * Cleans up allocated textures and cached text textures.
         */
        ~Graphics() {
            // Clean up the textures
            for (auto& pair : textures) {
                SDL_DestroyTexture(pair.second);
                pair.second = nullptr;
            }
            textures.clear();

            // Clean up the text cache
            for (auto& pair : textCache) {
                SDL_DestroyTexture(pair.second.texture.get());
            }
            textCache.clear();
            accessQueue.clear();
        }

        /**
         * Draw a line on the screen.
         * \param color The color of the line.
         * \param from Starting point of the line.
         * \param to Ending point of the line.
         */
        void line(SDL_Color color, Utils::Vector2D from, Utils::Vector2D to);

        /**
         * Draw a rectangle outline on the screen.
         * \param color The color of the rectangle outline.
         * \param rect The rectangle's dimensions.
         */
        void rectangle(SDL_Color color, SDL_Rect rect);

        void rotatedRectangle(SDL_Color color, SDL_Rotated_Rect rotatedRect);

        /**
         * Fill a rectangle on the screen.
         * \param color The color to fill the rectangle with.
         * \param rect The rectangle's dimensions.
         */
        void fillRectangle(SDL_Color color, SDL_Rect rect);

        /**
         * Fill a rectangle on the screen with floating-point coordinates.
         * \param color The color to fill the rectangle with.
         * \param rect The rectangle's dimensions.
         */
        void fillRectangle(SDL_Color color, SDL_FRect rect);

        /**
         * Fill a rectangle outline on the screen.
         * \param color The color of the rectangle outline.
         * \param rect The rectangle's dimensions.
         */
        void fillRectangleOutline(SDL_Color color, SDL_Rect rect);

        /**
         * Fill a rectangle outline on the screen with floating-point coordinates.
         * \param color The color for the rectangle outline.
         * \param rect The rectangle's dimensions.
         */
        void fillRectangleOutline(SDL_Color color, SDL_FRect rect);

        /**
         * Render a texture on the screen.
         * \param tex The texture to render.
         * \param clip The portion of the texture to render (optional).
         * \param rend The rendering rectangle (optional).
         * \param angle The rotation angle (in degrees, optional).
         * \param flip The flip mode for rendering (optional).
         */
        void texture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

        /**
         * Render a string of text on the screen.
         * \param text The text to render.
         * \param font The font to use.
         * \param color The color of the text.
         * \param pos The position to render the text at.
         * \param alignment The text alignment (default is Left).
         */
        void string(std::string text, TTF_Font* font, SDL_Color color, Utils::Vector2D pos, int alignment = Left);

        /**
         * Get a cached or load a texture from a file.
         * \param filename The path to the texture file.
         * \return The loaded SDL_Texture.
         */
        SDL_Texture* getTexture(std::string filename);

        /**
         * Load a texture from a file.
         * \param filename The path to the texture file.
         * \return The loaded SDL_Texture.
         */
        SDL_Texture* loadTexture(std::string filename);

        /**
         * Retrieve a cached texture containing rendered text.
         * \param text The text to render.
         * \param font The font to use.
         * \param color The color of the text.
         * \return A shared pointer to the cached SDL_Texture.
         */
        std::shared_ptr<SDL_Texture> getText(std::string text, TTF_Font* font, SDL_Color color);

        /**
         * Create and cache a texture containing rendered text.
         * \param text The text to render.
         * \param font The font to use.
         * \param color The color of the text.
         * \return A shared pointer to the cached SDL_Texture.
         */
        std::shared_ptr<SDL_Texture> createTextTexture(std::string text, TTF_Font* font, SDL_Color color);

        void sdl_rotated_rect(SDL_Renderer *r, SDL_Rotated_Rect rotatedRect);

    }; extern Graphics* g_drawing;

} // Drawing

#endif //BOSCONIAN_GRAPHICS_H
