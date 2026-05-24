#ifndef _SPRITESHEET_
#define _SPRITESHEET_

#include <raylib.h>
#include <unordered_map>
#include <vector>

struct SpriteSheetConfig {
    Texture2D* spriteSheet;

    char spriteWidth, spriteHeight;
};

class SpriteSheet {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    static SpriteSheet empty;
    
    //===CONSTRUCTORS===
    SpriteSheet(Texture2D* spriteSheet, const unsigned& spriteWidth, const unsigned& spriteHeight, const std::vector<unsigned>& framesPerLayer);
    SpriteSheet(const SpriteSheet& other);

    //===DESTRUCTOR===
    ~SpriteSheet() = default;
    
    //===GETTERS===
    Texture2D* GetSpriteSheet();
    
    //===SETTERS===
    const std::vector<std::vector<Rectangle>>& GetSpriteSheetMatrix();
    
    //===MEMBER FUNCTIONS===
    bool IsEmpty() const;

    Rectangle GetFrameRect(unsigned layer, unsigned frameIdx) const;
private:
    Texture2D* spriteSheet;

    std::unordered_map<unsigned, std::vector<Rectangle>> stateAnimations;
    std::vector<std::vector<Rectangle>> spriteSheetMatrix;

    int spriteWidth, spriteHeight;
};

#endif