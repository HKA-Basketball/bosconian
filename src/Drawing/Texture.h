#ifndef BOSCONIAN_TEXTURE_H
#define BOSCONIAN_TEXTURE_H

#include "Graphics.h"
#include "../../includes.h"
#include "../Utilities/GlobalVars.h"

namespace Drawing {

    class Texture {
    private:
        Drawing::Graphics* g_drawing;

        std::string name;

        SDL_Texture* imgTex; // The SDL_Texture associated with the image
        bool clipped; // Flag indicating if the texture is clipped
        SDL_Rect renderRect; // The rendering rectangle for the texture
        SDL_Rect clipRect; // The clipping rectangle for the texture
        float angle; // Rotation angle in degrees

    public:

        /**
         * Constructor for the Texture class.
         * \param filename Path to the image file.
         * \param deg Rotation angle in degrees (default is 0).
         * \param clipped Flag indicating if the texture is clipped (default is false).
         * \param spritesheet Path to the spritesheet (default is empty).
         */
        Texture(std::string filename, float deg = 0.f, bool clipped = false, std::string spritesheet = "");

        /**
         * Change the texture of the object.
         * \param filename Path to the new image file.
         * \param clipped Flag indicating if the texture is clipped (default is false).
         * \param spritesheet Path to the spritesheet (default is empty).
         * \return True if the texture change was successful, otherwise false.
         */
        bool changeTexture(std::string filename, bool clipped = false, std::string spritesheet = "");

        /**
         * Set the size of the texture.
         * \param newSize New size for the texture.
         */
        void setSize(Utils::Vector2D newSize);

        /**
         * Get the size of the texture.
         * \return The size of the texture as a Vector2D.
         */
        Utils::Vector2D getSize();

        /**
         * Set the position of the texture.
         * \param newPos New position for the texture.
         */
        void setPos(Utils::Vector2D newPos);

        /**
         * Get the position of the texture.
         * \return The position of the texture as a Vector2D.
         */
        Utils::Vector2D getPos();

        /**
         * Set the rotation angle of the texture.
         * \param newAngle New rotation angle in degrees.
         */
        void setAngle(float newAngle);

        /**
         * Get the rotation angle of the texture.
         * \return The rotation angle of the texture in degrees.
         */
        float getAngle();

        /**
         * Draw the texture on the screen.
         */
        void draw();

    };

} // Drawing

#endif //BOSCONIAN_TEXTURE_H
