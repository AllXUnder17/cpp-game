#ifndef _ENTITY_
#define _ENTITY_

#include "core/gameobject.h"
#include "core/spritesheet.h"

class Entity : public GameObject {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Entity(const GameObjectConfig& config, const SpriteSheet& spriteSheet);
    
    //===DESTRUCTOR===
    
    //===GETTERS===
    SpriteSheet& GetSpriteSheet() const;

    //===SETTERS===
    void SetSpriteSheet(const SpriteSheet& sheet);
    
    //===MEMBER FUNCTIONS===
    void OnUpdate() override;
    void Draw() override;
    
protected:
    SpriteSheet spriteSheet;

    bool isFacingLeft;
    
private:
    float elapsedFrameTime = 0.0f;
    char currFrameIdx = 0;
};

#endif