#include "collisionmanager.h"

#include <algorithm>

//===CONSTANTS===

//===STATIC MEMBERS===
std::vector<ICollidable*> CollisionManager::collidables = std::vector<ICollidable*>();

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===s

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

