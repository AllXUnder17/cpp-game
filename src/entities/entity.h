#ifndef _ENTITY_
#define _ENTITY_

#include "core/gameobject.h"
#include "core/spritesheet.h"

struct EntityConfig {
    GameObjectConfig goConfig;
    SpriteSheet spriteSheet;
    Vector2 size;
    CollisionLayer collisionLayer = CollisionLayer::DEFAULT;
};

class Entity : public GameObject, public ICollidable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Entity(const EntityConfig& config);
    Entity(const Entity& other);
    
    //===DESTRUCTOR===
    ~Entity() = default;

    //===OPERATORS===
    Entity& operator=(const Entity& other);
    
    //===GETTERS===
    CollisionLayer GetCollisionLayer() override;

    SpriteSheet& GetSpriteSheet() const;

    BoundingBox& GetHitbox() override;

    bool IsColliderActive() override final;

    //===SETTERS===
    void SetSpriteSheet(const SpriteSheet& sheet);
    void SetAnimationLayer(char currAnimLayerIdx);
    
    //===MEMBER FUNCTIONS===
    void OnUpdate() override;
    void Draw() override;
    
    protected:
    SpriteSheet spriteSheet;
    
    BoundingBox hitbox;
    Vector2 size;
    
    bool isFacingLeft;
    
private:
    CollisionLayer collisionLayer;

    float elapsedFrameTime;
    char currFrameIdx;
    char currAnimLayerIdx;

    void SetHitbox();
    void HandleAnimation(const std::vector<std::vector<Rectangle>>& animationMatrix);
};

#endif