#ifndef _ENTITY_
#define _ENTITY_

#include "core/gameobject.h"
#include "core/managers/delegate.h"
#include "core/spritesheet.h"

struct EntityConfig {
    GameObjectConfig goConfig;
    SpriteSheet spriteSheet;
    Vector2 size;
    CollisionLayer collisionLayer = CollisionLayer::DEFAULT;
    Color spriteTint = WHITE;
};

class Entity : public GameObject, public ICollidable {
public:
    using FrameEventMap = std::unordered_map<int, Delegate<void()>>;

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

    BoundingBox GetHitbox() override;

    bool IsColliderActive() override final;

    char GetCurrFrameIdx() const;
    char GetCurrAnimLayerLength() const;

    Delegate<void()>& GetOnCurrAnimEndEvent();
    
    //===SETTERS===
    void SetSpriteSheet(const SpriteSheet& sheet);
    void SetAnimationLayer(char currAnimLayerIdx);

    void SetSpriteTint(const Color& tint);
    
    void SetIsActive(bool toggle) override;

    //---Handle Collider---
    void EnableCollider();
    void DisableCollider();
    
    //===MEMBER FUNCTIONS===
    void OnAwake() override;
    void OnDestroy() override;

    void OnUpdate() override;

    void Draw() override;

    void AddAnimationEvent(size_t animLayer, size_t frameIdx, size_t eventId, std::function<void()> callback);
    
protected:
    std::unordered_map<int, FrameEventMap> animationEvents;

    SpriteSheet spriteSheet;
    
    BoundingBox hitbox;
    Vector2 size;
    
    bool isFacingLeft;
    bool isColliderEnabled;
private:
    CollisionLayer collisionLayer;
    Color spriteTint;

    float elapsedFrameTime;
    char currFrameIdx;
    char currAnimLayerIdx;

    Delegate<void()> onCurrAnimEndEvent;

    void SetHitbox();
    void HandleAnimation(const std::vector<std::vector<Rectangle>>& animationMatrix);
};

#endif