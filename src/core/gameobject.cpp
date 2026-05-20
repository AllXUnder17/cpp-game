#include "raylib.h"
#include "raymath.h"

#include "gameobject.h"
#include "gamemanager.h"

size_t GameObject::COUNTER = 0;

//===CONSTRUCTORS===

GameObject::GameObject(const GameObjectConfig& config) {
    id = ++GameObject::COUNTER;

    this->position = config.position;
    this->localPosition = config.localPosition;

    this->sprite = config.sprite;
    this->rotation = config.rotation;
    this->parent = config.parent;

    GameManager& gm = GameManager::GetInstance();
    gm.AddDrawable(this);
    gm.AddUpdatable(this);
}

size_t GameObject::GetID() const {
    return id;
}

Vector2 GameObject::GetPosition() const {
    return position;
}

void GameObject::SetPosition(Vector2 position, bool isWorldPos) {
    if (!isWorldPos && parent != nullptr) {
        position.x += parent->position.x;
        position.y += parent->position.y;
    }
    else if (isWorldPos)
        this->position = position;
}

//===METHODS===

void GameObject::Draw() const {
    Rectangle source = { 0.0f, 0.0f, (float)(*sprite).width, (float)(*sprite).height };
    Rectangle dest = { position.x, position.y, (float)(*sprite).width, (float)(*sprite).height };
    
    // Set the handle rotation point (adjust these offsets based on your custom sprite)
    Vector2 origin = { (float)(*sprite).width / 2, (float)(*sprite).height / 2 }; 

    // Draw the gun inside the camera-tracked world space
    DrawTexturePro(*sprite, source, dest, origin, rotation, (Color){ 255, 255, 255, 255 } );
}

void GameObject::OnUpdate() { 
    this->position.x = parent->position.x + this->localPosition.x;
    this->position.y = parent->position.y + this->localPosition.y;
}