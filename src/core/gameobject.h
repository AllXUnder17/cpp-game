#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <cstddef>

#include "ionend.h"
#include "ionstart.h"
#include "raylib.h"

#include "idrawable.h"
#include "iupdatable.h"
#include "icollidable.h"

class GameObject;

struct GameObjectConfig {
    std::string tag = "---";

    Texture2D *sprite = nullptr;
    GameObject *parent = nullptr;

    Vector2 position = { 0, 0 };
    Vector2 localPosition = { 0, 0 };

    Vector2 anchor = { 0, 0 };

    float rotation = 0.0f;
    float localRotation = 0.0f;

    bool isActive = true;
};

class GameObject : public IDrawable, public IUpdatable, public IOnStart, public IOnEnd {
public:
    //===CONSTANTS===

    //===STATIC MEMBERS===
    static size_t COUNTER;

    //===CONSTRUCTORS===
    GameObject(const GameObjectConfig& config);
    GameObject(const GameObject& other);

    GameObject& operator=(const GameObject& other);

    //===DESTRUCTOR===
    ~GameObject();
    
    //===OPERATORS===
    
    //===GETTERS===
    size_t GetID() const;

    const Vector2& GetPosition() const;
    const Vector2& GetLocalPosition() const;

    float GetRotation() const;

    bool IsActive() const;

    const std::string& GetTag() const; 
    
    //===SETTERS===
    void SetPosition(const Vector2& position);
    void SetLocalPosition(const Vector2& localPosition);
    
    void SetRotation(float rotation);
    void SetLocalRotation(float localRotation);
    
    void SetPositionAndRotation(const Vector2& position, const float& rotation);
    
    void SetIsActive(bool isActive);
    
    //===MEMBER FUNCTIONS===
    //---Inheriteds---
    void Draw() override;
    
    void OnStart() override {}
    void OnUpdate() override;
    void OnEnd() override {}

protected:
    std::string tag;

    GameObject *parent;
    Texture2D *sprite;

    Vector2 position;
    Vector2 localPosition;
    
    Vector2 anchor;

    // Rectangle hitbox

    size_t id;
    
    float rotation;
    float localRotation;
    
    float scale;
    
    bool isActive;

    void UpdatePosition();
    void UpdateRotation();
};

#endif
