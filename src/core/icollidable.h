#ifndef _ICOLLIDABLE_
#define _ICOLLIDABLE_

class GameObject;

class ICollidable {
public:
    ~ICollidable() = default;
    
    virtual void OnCollisionEnter(const GameObject& other) {};
    virtual void OnCollisionExit(const GameObject& other) {};

    virtual void OnTriggerEnter(const GameObject& other) {};
    virtual void OnTriggerUpdate(const GameObject& other) {};
    virtual void OnTriggerExit(const GameObject& other) {};

private:
    
};

#endif