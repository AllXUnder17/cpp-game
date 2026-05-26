#ifndef _COLLISION_MANAGER_
#define _COLLISION_MANAGER_

#include <vector>

#include "core/icollidable.h"

class CollisionManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static std::vector<ICollidable*>& GetCollidables();

    static void AddCollidable(ICollidable* collidable);
private:
    static std::vector<ICollidable*> collidables;
};

#endif