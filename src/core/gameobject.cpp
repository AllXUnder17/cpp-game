#include "raylib.h"

#include "gameobject.h"

#include "managers/scenemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===
size_t GameObject::COUNTER = 0;

//===CONSTRUCTORS===
GameObject::GameObject(const GameObjectConfig& config) {
    id = ++GameObject::COUNTER;

    this->name = config.name;
    this->tag = config.tag;

    this->position = config.position;
    this->localPosition = config.localPosition;

    this->sprite = config.sprite;

    this->rotation = config.rotation;
    this->localRotation = config.localRotation;

    this->parent = config.parent;

    this->isActive = config.isActive;
    this->isDead = false;
}

GameObject::GameObject(const GameObject& other) : sprite(other.sprite) {
    id = ++GameObject::COUNTER;

    this->name = other.name;
    this->tag = other.tag;

    this->position = other.position;
    this->localPosition = other.localPosition;

    this->rotation = other.rotation;
    this->localRotation = other.localRotation;

    this->parent = other.parent;

    this->isActive = other.isActive;
    this->isDead = false;
}


GameObject& GameObject::operator=(const GameObject& other) {
    if (this == &other)
        return *this;

    id = ++GameObject::COUNTER;

    this->position = other.position;
    this->localPosition = other.localPosition;

    this->rotation = other.rotation;
    this->localRotation = other.localRotation;

    this->parent = other.parent;

    this->isActive = other.isActive;

    this->sprite = other.sprite;

    return *this;
}

//===DESTRUCTOR===
GameObject::~GameObject() {
    //GameManager::Destroy(this);
}

//===OPERATORS===

//===GETTERS===
size_t GameObject::GetID() const {
    return id;
}

const Vector2& GameObject::GetPosition() const {
    return position;
}

const Vector2& GameObject::GetLocalPosition() const {
    return localPosition;
}

float GameObject::GetRotation() const {
    return rotation;
}

bool GameObject::IsActive() const {
    return isActive;
}

bool GameObject::IsDrawableActive() {
    return isActive;
}

const std::string& GameObject::GetTag() const {
    return tag;
}

bool GameObject::GetIsDead() const {
    return isDead;
}

//===SETTERS===
void GameObject::SetTag(const std::string& tag) {
    this->tag = tag;
}

void GameObject::SetPosition(const Vector2& position) {
    //this->position = utils::RoundToDigit(position, 2);
    this->position = position;
}

void GameObject::SetLocalPosition(const Vector2& localPosition) {
    this->localPosition = localPosition;
}

void GameObject::SetRotation(float rotation) {
    this->rotation = rotation;
}

void GameObject::SetLocalRotation(float localRotation) {
    this->localRotation = localRotation;
}

void GameObject::SetIsActive(bool isActive) {
    this->isActive = isActive; 
}

void GameObject::SetIsDead(bool isDead) {
    this->isDead = isDead;
}

//===MEMBER FUNCTIONS===
void GameObject::OnAwake() {
    GFXManager::AddDrawable(this);
}

void GameObject::OnDestroy() {
    GFXManager::RemoveDrawable(this);
}


void GameObject::Draw() {
    if (!isActive || sprite == nullptr)
        return;

    Rectangle source = { 0.0f, 0.0f, (float)(*sprite).width, (float)(*sprite).height };
    Rectangle dest = { position.x, position.y, (float)(*sprite).width, (float)(*sprite).height };
    
    Vector2 origin = { (float)(*sprite).width / 2, (float)(*sprite).height / 2 }; 

    DrawTexturePro(*sprite, source, dest, origin, rotation, (Color){ 255, 255, 255, 255 } );
}

void GameObject::OnUpdate() { 
    if (!isActive)
        return;

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