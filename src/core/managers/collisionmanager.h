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

    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===

private:
    static std::vector<ICollidable*> collidables;

    static void DrawDebugColliders();
};

#endif