#include "entity.h"
#include <cstdlib>
#include "core/managers/gfxmanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Entity::Entity(const GameObjectConfig& config, const SpriteSheet& spriteSheet) 
    : GameObject(config), spriteSheet(spriteSheet), isFacingLeft(false) { }

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===
// void Entity::SetVelocity(const Vector2& vel) {
//     this.
// }

//===MEMBER FUNCTIONS===

void Entity::OnUpdate() {
    elapsedFrameTime += GetFrameTime();
    // TraceLog(LOG_INFO, "Entity::OnUpdate");
    // // TraceLog(LOG_INFO, std::to_string(currFrameIdx).c_str());
    // // TraceLog(LOG_INFO, std::to_string(1.0f/12).c_str());
    // TraceLog(LOG_INFO, std::to_string(elapsedFrameTime).c_str());

    if (elapsedFrameTime >= GFXManager::FRAME_WAIT_TIME) {
        // TraceLog(LOG_INFO, "Changed Frame");
        currFrameIdx = (currFrameIdx + 1) % 2;
        elapsedFrameTime = 0.0f;
    }
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