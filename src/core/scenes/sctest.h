#ifndef _SCTEST_
#define _SCTEST_

#include "scene.h"

#include "core/managers/gfxmanager.h"

class SCTest : public Scene {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    SCTest(const std::string& name) : Scene(name) { }
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void OnLoad() override;
    void OnUpdate(float deltaTime) override;
    void OnUnload() override;

private:
    
};

void SCTest::OnLoad() {
    GFXManager::BACKGROUND_COLOR = BROWN;
    
    EnemyFactory::SpawnBaseEnemy({40, 40});
}


void SCTest::OnUpdate(float deltaTime) {
    Scene::OnUpdate(deltaTime);
    
    CollectableFactory::OnUpdate(deltaTime);
}


void SCTest::OnUnload() { 
    Scene::OnUnload();
}

#endif