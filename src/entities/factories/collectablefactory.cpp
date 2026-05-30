#include "collectablefactory.h"

#include "core/spriteloader.h"
#include "core/managers/gamemanager.h"

#include "entities/coin.h"

//===CONSTANTS===

//===STATIC MEMBERS===
Coin* CollectableFactory::baseCoinPrefab = nullptr;

//===CONSTRUCTORS===
void CollectableFactory::Init() {
    InitPrefabs();
}

//===DESTRUCTOR===
void CollectableFactory::Uninit() {
    baseCoinPrefab = nullptr;
}

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void CollectableFactory::InitPrefabs() {
    baseCoinPrefab = new Coin(EntityConfig{
        GameObjectConfig{
            .position = {40, -40}
        },
        SpriteSheet(
            SpriteLoader::GetSprite("coin_spritesheet.png"),
            16, 16, {2} 
        ), Vector2{8., 8}});
}

Coin* CollectableFactory::SpawnCoin(const Vector2& pos) {
    Coin* clone = GameManager::InstantiateGameObject<Coin>(*baseCoinPrefab);
    clone->SetPosition(pos);

    return clone;
}