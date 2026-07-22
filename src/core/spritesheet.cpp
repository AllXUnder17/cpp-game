#include "spritesheet.h"

//===CONSTANTS===

//===STATIC MEMBERS===
SpriteSheet SpriteSheet::empty = SpriteSheet(nullptr, 0, 0, {});

//===CONSTRUCTORS===
SpriteSheet::SpriteSheet(Sprite* spriteSheet, const unsigned spriteWidth, const unsigned spriteHeight, const std::vector<unsigned>& framesPerRow) {
    this->spriteSheet = spriteSheet;
    
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;

    this->framesPerRow = framesPerRow;

    // (Removed the redundant stateAnimations map assignment here, C++ handles it automatically)

    if (spriteSheet) {
        int defaultColumns = spriteSheet->texture->width / spriteWidth;
        int rows = spriteSheet->texture->height / spriteHeight;

        spriteSheetMatrix.resize(rows); // Allocate space for each row/state

        for (int row = 0; row < rows; row++) {
            // If we passed an array defining specific frame counts for this row, use it.
            // Otherwise, fallback to the default max columns.
            int colsInThisRow = (row < framesPerRow.size()) ? framesPerRow.at(row) : defaultColumns;

            for (int col = 0; col < colsInThisRow; col++) {
                Rectangle frameBox = {
                    (float)(col * spriteWidth),
                    (float)(row * spriteHeight),
                    (float)spriteWidth,
                    (float)spriteHeight
                };
                spriteSheetMatrix.at(row).push_back(frameBox);
                stateAnimations[row].push_back(frameBox);
            }
        }
    }
}

SpriteSheet::SpriteSheet(const SpriteSheet& other) {
    this->spriteSheet = other.spriteSheet;
    
    this->spriteWidth = other.spriteWidth;
    this->spriteHeight = other.spriteHeight;

    this->framesPerRow = other.framesPerRow;

    if (spriteSheet) {
        int defaultColumns = spriteSheet->texture->width / spriteWidth;
        int rows = spriteSheet->texture->height / spriteHeight;

        spriteSheetMatrix.resize(rows); // Allocate space for each row/state

        for (int row = 0; row < rows; row++) {
            // If we passed an array defining specific frame counts for this row, use it.
            // Otherwise, fallback to the default max columns.
            int colsInThisRow = (row < framesPerRow.size()) ? framesPerRow.at(row) : defaultColumns;

            for (int col = 0; col < colsInThisRow; col++) {
                Rectangle frameBox = {
                    (float)(col * spriteWidth),
                    (float)(row * spriteHeight),
                    (float)spriteWidth,
                    (float)spriteHeight
                };
                spriteSheetMatrix.at(row).push_back(frameBox);
                stateAnimations[row].push_back(frameBox);
            }
        }
    }
}

//===DESTRUCTOR===
// SpriteSheet::~SpriteSheet() {
//     this->spriteSheet = nullptr;
// }

//===GETTERS===
Sprite* SpriteSheet::GetSpriteSheet() const {
    return spriteSheet;
}

const std::vector<std::vector<Rectangle>>& SpriteSheet::GetSpriteSheetMatrix() const {
    return spriteSheetMatrix;
}

//===SETTERS===

//===MEMBER FUNCTIONS===

bool SpriteSheet::IsEmpty() const {
    return spriteSheet == nullptr;
}

Rectangle SpriteSheet::GetFrameRect(unsigned layer, unsigned frameIndex) const {
    auto it = stateAnimations.find(layer);
    
    //TraceLog(LOG_WARNING, std::to_string(it->second.size()).c_str());

    if (it != stateAnimations.end() && frameIndex < (int)it->second.size()) {
        return it->second[frameIndex];
    }

    return Rectangle{ 0, 0, 0, 0 }; // Fallback
}