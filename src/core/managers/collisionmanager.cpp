#include "collisionmanager.h"

#include <algorithm>

//===CONSTANTS===

//===STATIC MEMBERS===
std::vector<ICollidable*> CollisionManager::collidables = std::vector<ICollidable*>();

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===GETTERS===
std::vector<ICollidable*>& CollisionManager::GetCollidables() {
    return collidables;
}
std::vector<ICollidable*> CollisionManager::GetActiveCollidables() {
    std::vector<ICollidable*> activeCollidables;
    std::copy_if(collidables.begin(), collidables.end(), std::back_inserter(activeCollidables), [](ICollidable* collidable) { return collidable->IsColliderActive(); });

    return activeCollidables;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
void CollisionManager::OnUpdate() {
    CollisionManager::DrawDebugColliders();

    //Can be optimized
    std::vector<ICollidable*> activeCollidables = GetActiveCollidables();

    for (auto collidable1 : activeCollidables) {
        for (auto collidable2 : activeCollidables) {
            if (collidable1 != collidable2) {
                if (CheckCollisionBoxes(collidable1->GetHitbox(), collidable2->GetHitbox()))
                    collidable1->OnCollisionEnter(collidable2);
            }
        }
    }
}

void CollisionManager::DrawDebugColliders() {
    // Only run this if we actually have objects to display
    if (collidables.empty()) return;

    // Define a bright, transparent color so we can see through the box overlay
    Color colliderColor = Color{ 0, 228, 48, 100 }; // Transparent Green (Lime)
    Color outlineColor  = Color{ 0, 228, 48, 255 }; // Solid Green Outline

    for (ICollidable* collidable : collidables) {
        if (collidable == nullptr) continue;

        BoundingBox box = collidable->GetHitbox();

        DrawBoundingBox(box, outlineColor);
    }
}


void CollisionManager::AddCollidable(ICollidable* collidable) {
    collidables.push_back(collidable);
}

void CollisionManager::RemoveCollidable(ICollidable* collidable) {
    auto it = std::find(collidables.begin(), collidables.end(), collidable);

    if (it != collidables.end())
        collidables.erase(it);
}