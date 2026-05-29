#ifndef _COLLISION_MANAGER_
#define _COLLISION_MANAGER_

#include <vector>

#include "core/gameobject.h" // IWYU pragma: keep
#include "core/icollidable.h"
#include "core/iupdatable.h"  // IWYU pragma: keep

class CollisionManager {
public:
    //===CONSTANTS===
    CollisionManager() = delete;
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    static std::vector<ICollidable*>& GetCollidables();
    static std::vector<ICollidable*> GetActiveCollidables();
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static void OnUpdate();

    static void AddCollidable(ICollidable* collidable);
    static void RemoveCollidable(ICollidable* collidable);
private:
    static std::vector<ICollidable*> collidables;

    static void DrawDebugColliders();
};

#endif