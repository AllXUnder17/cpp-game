#ifndef _SPRITESHEET_
#define _SPRITESHEET_

#include "sprite.h"
#include <raylib.h>
#include <unordered_map>
#include <vector>


class SpriteSheet {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    static SpriteSheet empty;
    
    //===CONSTRUCTORS===
    SpriteSheet(Sprite* spriteSheet, const unsigned spriteWidth, const unsigned spriteHeight, const std::vector<unsigned>& framesPerLayer);
    SpriteSheet(const SpriteSheet& other);

    //===DESTRUCTOR===
    ~SpriteSheet() = default;
    
    //===GETTERS===
    Sprite* GetSpriteSheet() const;
    const std::vector<std::vector<Rectangle>>& GetSpriteSheetMatrix() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    bool IsEmpty() const;

    Rectangle GetFrameRect(unsigned layer, unsigned frameIdx) const;
private:
    Sprite* spriteSheet;

    std::unordered_map<unsigned, std::vector<Rectangle>> stateAnimations;
    std::vector<std::vector<Rectangle>> spriteSheetMatrix;

    std::vector<unsigned> framesPerRow;

    int spriteWidth, spriteHeight;
};

#endif