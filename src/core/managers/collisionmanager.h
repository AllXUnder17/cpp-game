#ifndef _COLLISION_MANAGER_
#define _COLLISION_MANAGER_

#include <vector>

#include "core/icollidable.h"
#include "core/iupdatable.h"

class CollisionManager : public IUpdatable {
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