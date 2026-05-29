#ifndef _ICOLLIDABLE_
#define _ICOLLIDABLE_

#include "raylib.h"


class ICollidable {
public:
    ~ICollidable() = default;

    virtual BoundingBox& GetHitbox() = 0;
    virtual bool IsColliderActive() = 0;
    
    virtual void OnCollisionEnter(ICollidable* other) {};
    virtual void OnCollisionExit(ICollidable* other) {};

    virtual void OnTriggerEnter(ICollidable* other) {};
    virtual void OnTriggerUpdate(ICollidable* other) {};
    virtual void OnTriggerExit(ICollidable* other) {};

private:
    
};

#endif