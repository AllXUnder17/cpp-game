#include "collectablefactory.h"

#include "core/spriteloader.h"
#include "core/managers/gamemanager.h"

#include "entities/coin.h"

//===CONSTANTS===

//===STATIC MEMBERS===
Coin* CollectableFactory::baseCoinPrefab = nullptr;

float CollectableFactory::collectableSpawnTime = 1;
float CollectableFactory::elapsedCoinSpawnTime = 0;

//===CONSTRUCTORS===
void CollectableFactory::Init(float collectableSpawnTime) {
    InitPrefabs();

    CollectableFactory::collectableSpawnTime = collectableSpawnTime;
}

//===DESTRUCTOR===
void CollectableFactory::Uninit() {
    baseCoinPrefab = nullptr;
}

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void CollectableFactory::OnUpdate(float deltaTime) {
    elapsedCoinSpawnTime += deltaTime;

    if (elapsedCoinSpawnTime >= collectableSpawnTime) {
        //vurti zarche za koi collectable da spawnne
        Vector2 pos = {(float)GetRandomValue(-40, 40), (float)GetRandomValue(-40, 40)};

        //ako e moneta
        SpawnCoin(pos);
        elapsedCoinSpawnTime = 0.0f;
    }
}

void CollectableFactory::InitPrefabs() {
    baseCoinPrefab = new Coin(EntityConfig{
        GameObjectConfig{
            .position = {40, -40},
            .isActive = false
        },
        SpriteSheet(
            SpriteLoader::GetSprite("coin_spritesheet.png"),
            16, 16, {2} 
        ), Vector2{8., 8}, CollisionLayer::COLLECTABLE});
}

Coin* CollectableFactory::SpawnCoin(const Vector2& pos) {
    Coin* clone = GameManager::InstantiateGameObject<Coin>(*baseCoinPrefab);
    clone->SetPosition(pos);
    clone->SetIsActive(true);
    return clone;
}