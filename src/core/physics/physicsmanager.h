#ifndef _PHYSICS_MANAGER_
#define _PHYSICS_MANAGER_

#include <ostream>
#include <unordered_map>
#include <vector>

#include "collisionlayer.h"
#include "core/icollidable.h"

class PhysicsManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    static void Init();

    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    static std::vector<ICollidable*>& GetCollidables();
    static std::vector<ICollidable*> GetActiveCollidables();
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static bool CanCollide(CollisionLayer colA, CollisionLayer colB);
    static void UpdateCollision();

    static void OutputInfo(std::stringstream& ss);

    //---Collidables---
    static void AddCollidable(ICollidable* collidable);
    static void RemoveCollidable(ICollidable* collidable);
private:
    PhysicsManager() = delete;

    static std::vector<ICollidable*> collidables;
    static std::unordered_map<CollisionLayer, unsigned int> layerMatrix;
};

#endif