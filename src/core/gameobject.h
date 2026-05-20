#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <cstddef>

#include "raylib.h"

#include "idrawable.h"
#include "iupdatable.h"

class GameObject;

struct GameObjectConfig {
    Texture2D *sprite = nullptr;
    GameObject *parent = nullptr;

    Vector2 position = { 0, 0 };
    Vector2 localPosition = { 0, 0 };

    Vector2 anchor = { 0, 0 };
    float rotation = 0.0f;
};

class GameObject : public IDrawable, public IUpdatable {
public:
    //---Constants---
    static size_t COUNTER;

    //---Constructors---
    GameObject(const GameObjectConfig& config);

    //---Getters---
    size_t GetID() const;

    Vector2 GetPosition() const;

    
    //---Setters---
    void SetPosition(Vector2 position, bool isWorldPos);
    void SetRotation(float rotation);
    void SetPositionAndRotation(Vector2 position, float rotation);

    //---Inheriteds---
    void Draw() const final;
    void OnUpdate();

protected:
    GameObject *parent;
    Texture2D *sprite;

    Vector2 position;
    Vector2 localPosition;
    
    Vector2 anchor;
    float rotation;
    float scale;

    size_t id;
};

#endif