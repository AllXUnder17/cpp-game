#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <cstddef>

#include "raylib.h"

#include "idrawable.h"
#include "iupdatable.h"
#include "icollidable.h"

class GameObject;

struct GameObjectConfig {
    Texture2D *sprite = nullptr;
    GameObject *parent = nullptr;

    Vector2 position = { 0, 0 };
    Vector2 localPosition = { 0, 0 };

    Vector2 anchor = { 0, 0 };

    float rotation = 0.0f;
    float localRotation = 0.0f;
};

class GameObject : public IDrawable, public IUpdatable /*, public ICollidable*/ {
public:
    //---Constants---
    static size_t COUNTER;

    //---Constructors---
    GameObject(const GameObjectConfig& config);
    //~GameObject();

    //---Getters---
    const size_t& GetID() const;

    const Vector2& GetPosition() const;
    const Vector2& GetLocalPosition() const;

    const float GetRotation() const;

    //---Setters---
    void SetPosition(const Vector2& position);
    void SetLocalPosition(const Vector2& localPosition);

    void SetRotation(const float& rotation);
    void SetLocalRotation(const float& localRotation);
    
    void SetPositionAndRotation(const Vector2& position, const float& rotation);

    //---Inheriteds---
    void Draw() override;
    void OnUpdate() override;

protected:
    GameObject *parent;
    Texture2D *sprite;

    Vector2 position;
    Vector2 localPosition;
    
    Vector2 anchor;

    // Rectangle hitbox

    float rotation;
    float localRotation;

    float scale;

    size_t id;

    void UpdatePosition();
    void UpdateRotation();
};

#endif