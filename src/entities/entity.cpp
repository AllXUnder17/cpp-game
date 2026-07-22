#include "entity.h"
#include <cstdlib>
#include "core/managers/gfxmanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Entity::Entity(const EntityConfig& config) 
    : GameObject(config.goConfig), spriteSheet(config.spriteSheet), isFacingLeft(false) {

    elapsedFrameTime = 0.0f;
    currFrameIdx = 0;
    currAnimLayerIdx = 0;

    this->size = config.size;
    this->collisionLayer = config.collisionLayer;
    this->spriteTint = config.spriteTint;

    onCurrAnimEndEvent = Delegate<void()>();

    EnableCollider();

    SetHitbox();
}

Entity::Entity(const Entity& other) : GameObject(other), spriteSheet(other.spriteSheet) {
    elapsedFrameTime = 0.0f;
    currFrameIdx = 0;
    currAnimLayerIdx = 0;

    this->size = other.size;
    this->collisionLayer = other.collisionLayer;
    this->spriteTint = other.spriteTint;

    // onCurrAnimEndEvent = Delegate<void()>();

    EnableCollider();

    SetHitbox();
}

//===DESTRUCTOR===
//~Entity() = default; 

//===OPERATORS===
Entity& Entity::operator=(const Entity& other) {
    if (this == &other)
        return *this;

    GameObject::operator=(other);
    spriteSheet = other.spriteSheet;

    elapsedFrameTime = 0.0f;
    currFrameIdx = 0;
    currAnimLayerIdx = 0;

    this->size = other.size;

    SetHitbox();

    return *this;
}

//===GETTERS===
const std::string Entity::GetObjectType() const {
    return "entity";
}

CollisionLayer Entity::GetCollisionLayer() {
    return collisionLayer;
}

BoundingBox Entity::GetHitbox() {
    return hitbox;
}

bool Entity::IsColliderActive() {
    return isColliderEnabled;
}

char Entity::GetCurrFrameIdx() const {
    return currFrameIdx;
}

char Entity::GetCurrAnimLayerLength() const {
    return spriteSheet.GetSpriteSheetMatrix()[currAnimLayerIdx].size();
}

Delegate<void()>& Entity::GetOnCurrAnimEndEvent() {
    return onCurrAnimEndEvent;
}

SpriteSheet& Entity::GetSpriteSheet() {
    return spriteSheet;
}

const Sprite* Entity::GetSprite() const {
    // if (sprite == nullptr)
    //     return spriteSheet.GetSpriteSheet();
    // else if (spriteSheet.GetSpriteSheet() == nullptr)
    //     return sprite;

    return nullptr;
}

//===SETTERS===
void Entity::SetSpriteSheet(const SpriteSheet& sheet) {
    spriteSheet = sheet;
}
void Entity::SetHitbox() {
    hitbox.min = Vector3{ position.x - size.x / 2, position.y - size.y / 2, 0.0f };
    hitbox.max = Vector3{ position.x + size.x / 2, position.y + size.y / 2, 0.0f };
}
void Entity::SetAnimationLayer(char newLayerIdx) {
    if (currAnimLayerIdx != newLayerIdx) {
        currAnimLayerIdx = newLayerIdx;
        currFrameIdx = 0;        // Reset back to frame 0 for the new animation!
        elapsedFrameTime = 0.0f; // Reset the clock tick
    }
}

void Entity::SetSpriteTint(const Color& tint) {
    this->spriteTint = tint;
}

void Entity::SetIsActive(bool toggle) {
    GameObject::SetIsActive(toggle);

    if (toggle)
        EnableCollider();
    else
        DisableCollider();
}

//---Collider---
void Entity::EnableCollider() {
    isColliderEnabled = true;
}
void Entity::DisableCollider() {
    isColliderEnabled = false;
}

//===MEMBER FUNCTIONS===
void Entity::OnAwake() {
    GameObject::OnAwake();

    PhysicsManager::AddCollidable(this);
}

void Entity::OnDestroy() {
    GameObject::OnDestroy();

    PhysicsManager::RemoveCollidable(this);
}

void Entity::OnUpdate() {
    GameObject::OnUpdate();

    SetHitbox();

    //---Animation handling---
    auto& matrix = spriteSheet.GetSpriteSheetMatrix();

    if (matrix.empty() || matrix[currAnimLayerIdx].empty())
        return;

    HandleAnimation(matrix);
}

void Entity::Draw() {
    if (spriteSheet.IsEmpty()) { 
        GameObject::Draw();

        return;
    }

    int layerIdx = currAnimLayerIdx;
    Rectangle sourceRec = this->spriteSheet.GetFrameRect(layerIdx, currFrameIdx);

    // If looking left, flip the source rectangle width
    if (isFacingLeft) sourceRec.width = -sourceRec.width;

    Texture2D* texture = spriteSheet.GetSpriteSheet()->texture;

    Rectangle destRec = { position.x, position.y, std::abs(sourceRec.width), sourceRec.height };
    Vector2 origin = { destRec.width / 2.0f, destRec.height / 2.0f };

    DrawTexturePro(*texture, sourceRec, destRec, origin, rotation, spriteTint);
}

void Entity::HandleAnimation(const std::vector<std::vector<Rectangle>>& animationMatrix) {
    elapsedFrameTime += GetFrameTime();

    if (elapsedFrameTime >= GFXManager::FRAME_WAIT_TIME) {
        currFrameIdx = (currFrameIdx + 1) % GetCurrAnimLayerLength();

        elapsedFrameTime = 0.0f;
    }

    if (currFrameIdx >= GetCurrAnimLayerLength() - 1)
        onCurrAnimEndEvent();

    auto layerIt = animationEvents.find(currAnimLayerIdx);
    if (layerIt != animationEvents.end()) {
        
        // 4. Look up if the current specific frame index has an active event
        auto frameIt = layerIt->second.find(currFrameIdx);
        if (frameIt != layerIt->second.end()) {
            
            // Fire the delegate! All registered functions execute instantly.
            frameIt->second(); 
        }
    }
}

void Entity::AddAnimationEvent(size_t animLayer, size_t frameIdx, size_t eventId, std::function<void()> callback) {
    animationEvents[animLayer][frameIdx].AddListener(eventId, callback);
}