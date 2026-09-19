#ifndef _ICOLLIDABLE_
#define _ICOLLIDABLE_

#include "raylib.h"

#include "physics/physicsmanager.h"
#include "physics/collisionlayer.h"

class GameObject;

class ICollidable {
private:
    GameObject* gobj;

public:
    virtual ~ICollidable() = default;

    virtual void SetICollidableGameObject(GameObject* gobj) { this->gobj = gobj; }
    virtual GameObject* GetGameObject() { return gobj; }

    virtual BoundingBox GetHitbox() = 0;
    virtual CollisionLayer GetCollisionLayer() = 0; 
    virtual bool IsColliderActive() = 0;
    
    virtual void OnCollisionEnter(ICollidable* other) {};
    virtual void OnCollisionExit(ICollidable* other) {};

    virtual void OnTriggerEnter(ICollidable* other) {};
    virtual void OnTriggerUpdate(ICollidable* other) {};
    virtual void OnTriggerExit(ICollidable* other) {};
};

#endif