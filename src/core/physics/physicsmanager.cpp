#include "physicsmanager.h"
#include "core/gameobject.h" // IWYU pragma: keep

#include "raylib.h"
#include <algorithm>
#include <iomanip> // IWYU pragma: keep


//===CONSTANTS===

//===STATIC MEMBERS===
std::unordered_map<CollisionLayer, unsigned int> PhysicsManager::layerMatrix;
std::vector<ICollidable*> PhysicsManager::collidables;

//===CONSTRUCTORS===
void PhysicsManager::Init() {
    layerMatrix.clear();

    layerMatrix[CollisionLayer::PLAYER] = CollisionLayer::DEFAULT | 
                                          CollisionLayer::ENEMY   | 
                                          CollisionLayer::ENEMY_PROJECTILE |
                                          CollisionLayer::COLLECTABLE;

    layerMatrix[CollisionLayer::ENEMY]  = CollisionLayer::DEFAULT | 
                                          CollisionLayer::PLAYER  | 
                                          CollisionLayer::PLAYER_PROJECTILE;

    layerMatrix[CollisionLayer::PLAYER_PROJECTILE] = CollisionLayer::DEFAULT | 
                                                     CollisionLayer::ENEMY;

    layerMatrix[CollisionLayer::ENEMY_PROJECTILE]  = CollisionLayer::DEFAULT | 
                                                     CollisionLayer::PLAYER;

}
//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
std::vector<ICollidable*>& PhysicsManager::GetCollidables() {
    return collidables;
}
std::vector<ICollidable*> PhysicsManager::GetActiveCollidables() {
    std::vector<ICollidable*> activeCollidables;
    std::copy_if(collidables.begin(), collidables.end(), std::back_inserter(activeCollidables), [](ICollidable* collidable) { return collidable->IsColliderActive(); });

    return activeCollidables;
}


//===SETTERS===

//===MEMBER FUNCTIONS===
bool PhysicsManager::CanCollide(CollisionLayer layerA, CollisionLayer layerB) {
    return (layerMatrix[layerA] & layerB) != 0;
}
void PhysicsManager::UpdateCollision() {
    std::vector<ICollidable*> activeCollidables = GetActiveCollidables();

    for (size_t i = 0; i < activeCollidables.size(); ++i) {
        for (size_t j = i + 1; j < activeCollidables.size(); ++j) {
            ICollidable* objA = activeCollidables[i];
            ICollidable* objB = activeCollidables[j];

            // UNITY LAYER FILTER: Check if these two layers are allowed to interact
            if (!CanCollide(objA->GetCollisionLayer(), objB->GetCollisionLayer()) && 
                !CanCollide(objB->GetCollisionLayer(), objA->GetCollisionLayer())) {
                continue; 
            }
            // If they are allowed to collide, NOW run your physical box bounds math
            if (CheckCollisionBoxes(objA->GetHitbox(), objB->GetHitbox())) {
                objA->OnCollisionEnter(objB);
                objB->OnCollisionEnter(objA);
            }
        }
    }
}

void PhysicsManager::OutputInfo(std::stringstream& ss) {
    ss << std::fixed << "PM: [ CNT: " << collidables.size() << ", ACTIVE_CNT: " << GetActiveCollidables().size() << "]\n\n";
}

//---Collidables---
void PhysicsManager::AddCollidable(ICollidable* collidable) {
    collidables.push_back(collidable);
}

void PhysicsManager::RemoveCollidable(ICollidable* collidable) {
    auto it = std::find(collidables.begin(), collidables.end(), collidable);

    if (it != collidables.end())
        collidables.erase(it);
}