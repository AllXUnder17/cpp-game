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

    SetHitbox();
}

Entity::Entity(const Entity& other) : GameObject(other), spriteSheet(other.spriteSheet) {
    elapsedFrameTime = 0.0f;
    currFrameIdx = 0;
    currAnimLayerIdx = 0;

    this->size = other.size;

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
BoundingBox& Entity::GetHitbox() {
    return hitbox;
}

bool Entity::IsColliderActive() {
    return IsActive();
}

//===SETTERS===
void Entity::SetSpriteSheet(const SpriteSheet& sheet) {
    spriteSheet = sheet;
}
void Entity::SetHitbox() {
    hitbox.min = Vector3{ position.x - size.x / 2, position.y - size.y / 2, 0.0f };
    hitbox.max = Vector3{ position.x + size.x / 2, position.y + size.y / 2, 0.0f };
}

//===MEMBER FUNCTIONS===

void Entity::OnUpdate() {
    GameObject::OnUpdate();

    SetHitbox();

    //---Animation handling---
    auto& matrix = spriteSheet.GetSpriteSheetMatrix();

    if (matrix.empty() || matrix[0].empty())
        return;

    HandleAnimation(matrix);
}

void Entity::Draw() {
    //TraceLog(LOG_INFO, "Entity::Draw");
    if (spriteSheet.IsEmpty()) { 
        GameObject::Draw();

        return;
    }

    int layerIdx = 0;
    // TraceLog(LOG_INFO, this->spriteSheet.IsEmpty() ? "1" : "0");
    Rectangle sourceRec = this->spriteSheet.GetFrameRect(layerIdx, currFrameIdx);

    // If looking left, flip the source rectangle width
    if (isFacingLeft) sourceRec.width = -sourceRec.width;

    Rectangle destRec = { position.x, position.y, std::abs(sourceRec.width), sourceRec.height };
    Vector2 origin = { destRec.width / 2.0f, destRec.height / 2.0f };

    DrawTexturePro(*spriteSheet.GetSpriteSheet(), sourceRec, destRec, origin, rotation, WHITE);
}

void Entity::HandleAnimation(const std::vector<std::vector<Rectangle>>& animationMatrix) {
    elapsedFrameTime += GetFrameTime();
    // TraceLog(LOG_INFO, "Entity::OnUpdate");
    // // TraceLog(LOG_INFO, std::to_string(currFrameIdx).c_str());
    // // TraceLog(LOG_INFO, std::to_string(1.0f/12).c_str());
    // TraceLog(LOG_INFO, std::to_string(elapsedFrameTime).c_str());

    if (elapsedFrameTime >= GFXManager::FRAME_WAIT_TIME) {
        currFrameIdx = (currFrameIdx + 1) % (animationMatrix[0]).size();
        // TraceLog(LOG_INFO, ("Curr Frame: " + std::to_string(spriteSheet.GetSpriteSheetMatrix()[0].size())).c_str());
        elapsedFrameTime = 0.0f;
    }
}