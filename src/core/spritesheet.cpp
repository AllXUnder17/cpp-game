#include "spritesheet.h"
#include <string>

//===CONSTANTS===

//===STATIC MEMBERS===
// FIX: Removed the curly braces {}. You are passing 3 arguments to the constructor, not a struct!
SpriteSheet SpriteSheet::empty = SpriteSheet(nullptr, 0, 0, {});

//===CONSTRUCTORS===
// OPTIONAL UPGRADE: You can add `const std::vector<unsigned>& framesPerRow = {}` to your .h file 
// to allow custom row lengths without needing a struct!
SpriteSheet::SpriteSheet(Texture2D* spriteSheet, const unsigned& spriteWidth, const unsigned& spriteHeight, const std::vector<unsigned>& framesPerRow) {
    this->spriteSheet = spriteSheet;
    
    // FIX: You forgot to save these in your original constructor! 
    // Your copy constructor was trying to copy uninitialized garbage data.
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;

    // (Removed the redundant stateAnimations map assignment here, C++ handles it automatically)

    if (spriteSheet) {
        int defaultColumns = spriteSheet->width / spriteWidth;
        int rows = spriteSheet->height / spriteHeight;

        spriteSheetMatrix.resize(rows); // Allocate space for each row/state

        for (int row = 0; row < rows; row++) {
            // If we passed an array defining specific frame counts for this row, use it.
            // Otherwise, fallback to the default max columns.
            int colsInThisRow = (row < framesPerRow.size()) ? framesPerRow[row] : defaultColumns;

            for (int col = 0; col < colsInThisRow; col++) {
                Rectangle frameBox = {
                    (float)(col * spriteWidth),
                    (float)(row * spriteHeight),
                    (float)spriteWidth,
                    (float)spriteHeight
                };
                spriteSheetMatrix[row].push_back(frameBox);
                stateAnimations[row].push_back(frameBox);
            }
        }
    }
}

SpriteSheet::SpriteSheet(const SpriteSheet& other) {
    this->spriteSheet = other.spriteSheet;
    this->spriteWidth = other.spriteWidth;
    this->spriteHeight = other.spriteHeight;
    
    this->spriteSheetMatrix = other.spriteSheetMatrix;
    this->stateAnimations = other.stateAnimations;
}

//===DESTRUCTOR===
// SpriteSheet::~SpriteSheet() {
//     this->spriteSheet = nullptr;
// }

//===GETTERS===
Texture2D* SpriteSheet::GetSpriteSheet() {
    return spriteSheet;
}

const std::vector<std::vector<Rectangle>>& SpriteSheet::GetSpriteSheetMatrix() {
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