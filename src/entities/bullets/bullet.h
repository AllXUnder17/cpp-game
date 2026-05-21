#ifndef _BULLET_
#define _BULLET_

#include "core/gameobject.h"

class Bullet : public GameObject {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Bullet(const GameObjectConfig& config, const Vector2& velocity);
    
    //===DESTRUCTOR===
    
    //===GETTERS===
    
    //===SETTERS===

    //===MEMBER FUNCTIONS===
    //void Draw() const;
    void OnUpdate() override;
private:
    Vector2 velocity;
};

#endif