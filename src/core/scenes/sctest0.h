#ifndef _A_
#define _A_

#include "scene.h"

#include "core/managers/gfxmanager.h"

class SCTest0 : public Scene {
public:
    //===CONSTRUCTORS===
    SCTest0(const std::string& name) : Scene(name) { }
    
    //===MEMBER FUNCTIONS===
    void OnLoad() override;
    void OnUpdate(float deltaTime) override;
    void OnUnload() override;
    
private:
    
};

void SCTest0::OnLoad() {
    GFXManager::BACKGROUND_COLOR = GRAY;
    
    Entity* portal = GameManager::InstantiateGameObjectInSCMain<Entity>(EntityConfig {
        GameObjectConfig {
            .name = "portal",
            .tag = "portal",
            .sprite = SpriteLoader::GetSprite("bullet.png"),
            .position = { 50, 50 }
        }
    });
}

void SCTest0::OnUpdate(float deltaTime) {
    Scene::OnUpdate(deltaTime);
}

void SCTest0::OnUnload() {
    Scene::OnUnload();
}

#endif