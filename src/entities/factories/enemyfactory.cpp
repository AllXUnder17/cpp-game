#include "enemyfactory.h"

#include "core/managers/gamemanager.h"

#include "core/spriteloader.h"

//===CONSTANTS===

//===STATIC MEMBERS===
Enemy* EnemyFactory::baseEnemyPrefab = nullptr;

//===CONSTRUCTORS===
void EnemyFactory::Init() {
    InitPrefabs();
}

//===DESTRUCTOR===
void EnemyFactory::Uninit() {
    baseEnemyPrefab = nullptr;
}

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void EnemyFactory::InitPrefabs() {
    baseEnemyPrefab = new Enemy(EntityConfig{
        GameObjectConfig{
            //.sprite = SpriteLoader::GetSprite()
            .position = {50, 50}
        },
        SpriteSheet(
            SpriteLoader::GetSprite("enemy_spritesheet.png"),
            80, 80, {9, 6, 12}
        ),
        Vector2 {40, 40}
    }, 0, 60);
}

Enemy* EnemyFactory::SpawnBaseEnemy(const Vector2& pos) {
    Enemy* clone = GameManager::InstantiateGameObject<Enemy>(*baseEnemyPrefab);

    clone->SetPosition(pos);

    return clone;
}