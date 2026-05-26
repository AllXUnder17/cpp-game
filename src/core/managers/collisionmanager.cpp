#include "collisionmanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===
std::vector<ICollidable*> CollisionManager::collidables = std::vector<ICollidable*>();

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
std::vector<ICollidable*>& CollisionManager::GetCollidables() {
    return collidables;
}

void CollisionManager::AddCollidable(ICollidable* collidable) {
    collidables.push_back(collidable);
}