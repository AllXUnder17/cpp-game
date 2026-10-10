#ifndef _SC_MAIN_
#define _SC_MAIN_

#include "core/scenes/scene.h"

#include "core/libraryofalexandria.h"

class Player;
class Weapon;

class SC_Main : public Scene {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    SC_Main(const std::string& name) : Scene(name) {
        TraceLog(LOG_INFO, "SCENE: Main scene instantiated");
    }
    
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

void SC_Main::OnLoad() {
    Player* player = GameManager::InstantiateGameObjectInSCMain<Player>(EntityConfig {
        GameObjectConfig { .name = "player", .tag = "Player" }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 16,
            {3}), Vector2 { 16,16 }, CollisionLayer::PLAYER}, 200);
    
    Weapon* w = GameManager::InstantiateGameObjectInSCMain<Weapon>(WeaponConfig {
        GameObjectConfig {
            .name = "weapon",
            .sprite = SpriteLoader::GetSprite("gun.png"),
            .parent = player,
            .localPosition = { 10, 5 }, 
        }, Vector2 { 12, -1 },
        5, 10, 10,  Sound()});


    SceneManager::LoadScene("Test0");
}

void SC_Main::OnUpdate(float deltaTime) {
    Scene::OnUpdate(deltaTime);
}

void SC_Main::OnUnload() {
    
}

#endif