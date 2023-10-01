#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../Utilities/Vector2D.h"
#include "../Utilities/Config.h"

struct Chunk {
    float x, y, width, height;
    bool occupied = false;

    bool contains(const Vector2D& position, const Vector2D& size = {0, 0}) const {
        float cornerPositionX = position.x - (size.x / 2);
        float cornerPositionY = position.y - (size.y / 2);

        if (x + width < cornerPositionX || cornerPositionX + size.x < x) {
            return false; // No horizontal overlap
        }

        if (y + height < cornerPositionY || cornerPositionY + size.y < y) {
            return false; // No vertical overlap
        }

        return true; // Intersection
    }
};


class World {
private:
    constexpr static const float mapWidth = Config::levelWidth;
    constexpr static const float mapHeight = Config::levelHeight;
    constexpr static const float chunkWidth = Config::chunkWidth;
    constexpr static const float chunkHeight = Config::chunkHeight;
    constexpr static const int numChunksX = static_cast<int>(mapWidth / chunkWidth);
    constexpr static const int numChunksY = static_cast<int>(mapHeight / chunkHeight);

    std::vector<Chunk> chunks;

    void initChunks() {
        for (int i = 0; i < numChunksY; ++i) {
            for (int j = 0; j < numChunksX; ++j) {
                Chunk chunk;
                chunk.x = j * chunkWidth;
                chunk.y = i * chunkHeight;
                chunk.width = chunkWidth;
                chunk.height = chunkHeight;
                chunks.push_back(chunk);
            }
        }
    }

public:

    World() { initChunks(); }

    void resetChunks() {
        chunks.clear();
        initChunks();
    }

    void markOccupied(const Vector2D& point, const Vector2D& size = {0, 0}) {
        for (auto& chunk : chunks) {
            if (chunk.contains(point, size)) {
                chunk.occupied = true;
            }
        }
    }

    std::vector<Chunk> getChunks() const {
        return chunks;
    }

    std::vector<Chunk> getUnoccupiedChunks() const {
        std::vector<Chunk> result;
        for (const auto& chunk : chunks) {
            if (!chunk.occupied) {
                result.push_back(chunk);
            }
        }
        return result;
    }

    std::vector<Chunk> getOccupiedChunks() const {
        std::vector<Chunk> result;
        for (const auto& chunk : chunks) {
            if (chunk.occupied) {
                result.push_back(chunk);
            }
        }
        return result;
    }

    std::vector<std::vector<Vector2D>> predefinedPositions() {
        std::vector<std::vector<Vector2D>> predefinedPositions = {
                // Set 1
                {
                        {150, 350},          // Random point
                        {360, 150},          // Random point
                        {280, 390}           // Random point
                },

                // Set 2
                {
                        {80, 100},           // Random point
                        {300, 280},          // Random point
                        {400, 440}           // Random point
                },

                // Set 3
                {
                        {430, 170},          // Random point
                        {220, 260},          // Random point
                        {90, 370}            // Random point
                },

                // Set 4
                {
                        {190, 80},           // Random point
                        {280, 450},          // Random point
                        {420, 250}           // Random point
                },

                // Set 5
                {
                        {70, 290},           // Random point
                        {380, 410},          // Random point
                        {250, 140}           // Random point
                }
        };

        return predefinedPositions;
    }


    // Wrap a position around the world boundaries
    static Vector2D wrapPosition(const Vector2D& position) {
        float wrappedX = std::fmod(std::fmod(position.x, mapWidth) + mapWidth, mapWidth);
        float wrappedY = std::fmod(std::fmod(position.y, mapHeight) + mapHeight, mapHeight);
        return {wrappedX, wrappedY};
    }
};

#endif //BOSCONIAN_WORLD_H
