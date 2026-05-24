#include "raylib.h"
#include "raymath.h"

#include "managers/gamemanager.h"
#include "managers/gfxmanager.h"

#include "gameobject.h"
#include "utils.h"

size_t GameObject::COUNTER = 0;

//===CONSTRUCTORS===

GameObject::GameObject(const GameObjectConfig& config) {
    id = ++GameObject::COUNTER;

    this->position = config.position;
    this->localPosition = config.localPosition;

    this->sprite = config.sprite;

    this->rotation = config.rotation;
    this->localRotation = config.localRotation;

    this->parent = config.parent;
    this->localRotation = config.localRotation;

    GFXManager::AddDrawable(this);
    GameManager::AddUpdatable(this);
}

const size_t& GameObject::GetID() const {
    return id;
}

const Vector2& GameObject::GetPosition() const {
    return position;
}

const Vector2& GameObject::GetLocalPosition() const {
    return localPosition;
}

const float GameObject::GetRotation() const {
    return rotation;
}

void GameObject::SetPosition(Vector2 position) {
    //this->position = utils::RoundToDigit(position, 2);
    this->position = position;
}

void GameObject::SetLocalPosition(Vector2 localPosition) {
    this->localPosition = localPosition;
}

void GameObject::SetRotation(float rotation) {
    this->rotation = rotation;
}

void GameObject::SetLocalRotation(float localRotation) {
    this->localRotation = localRotation;
}

//===METHODS===

void GameObject::Draw() {
    if (sprite == nullptr)
        return;

    Rectangle source = { 0.0f, 0.0f, (float)(*sprite).width, (float)(*sprite).height };
    Rectangle dest = { position.x, position.y, (float)(*sprite).width, (float)(*sprite).height };
    
    // Set the handle rotation point (adjust these offsets based on your custom sprite)
    Vector2 origin = { (float)(*sprite).width / 2, (float)(*sprite).height / 2 }; 

    // Draw the gun inside the camera-tracked world space
    DrawTexturePro(*sprite, source, dest, origin, rotation, (Color){ 255, 255, 255, 255 } );
}

void GameObject::OnUpdate() { 
    UpdatePosition();
    UpdateRotation();
}

void GameObject::UpdatePosition() {
    if (parent != nullptr) {
        this->position.x = parent->position.x + this->localPosition.x;
        this->position.y = parent->position.y + this->localPosition.y;
    }

    //position = utils::RoundToDigit(position, 2);
}

void GameObject::UpdateRotation() {
    if (parent != nullptr) {
        this->rotation = parent->rotation + this->rotation;
    }
}
