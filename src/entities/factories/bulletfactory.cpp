#include "bulletfactory.h"

#include "core/managers/gamemanager.h"
#include "core/managers/assetmanager.h"

#include "core/spriteloader.h"

#include "core/spritesheet.h"

#include <cstdlib>  // IWYU pragma: keep

//===CONSTANTS===

//===STATIC MEMBERS===
std::vector<Bullet*> BulletFactory::pool = std::vector<Bullet*>();

Bullet* BulletFactory::baseBulletPrefab = nullptr;

size_t BulletFactory::poolSize = 10;

//===CONSTRUCTORS===
void BulletFactory::Init() {
    //---Init prefabs---
    InitPrefabs();

    pool.reserve(poolSize);
}

void BulletFactory::Uninit() {
    delete baseBulletPrefab;
    baseBulletPrefab = nullptr;
}

void BulletFactory::InitPrefabs() {
    baseBulletPrefab = new Bullet(EntityConfig{
            GameObjectConfig {
                .name = "bullet-prefab",
                .sprite = SpriteLoader::GetSprite("bullet.png"), 
                .position = { -1000, -1000 }, 
                .isActive = false
            }, SpriteSheet::empty, Vector2{8., 8}, CollisionLayer::PLAYER_PROJECTILE}, 
            Vector2{0, 0}, 0);
}

//===MEMBER FUNCTIONS===
//---Inherited---

Bullet* BulletFactory::SpawnBullet(const Vector2& pos, const Vector2& vel, unsigned damage) {
    if (pool.size() == 0) {
        for (size_t i = 0; i < poolSize; ++i) {

            Bullet* b = GameManager::InstantiateGameObject<Bullet>(*baseBulletPrefab);
            b->SetName(("bullet-copy_" + std::to_string(i)).c_str());

            pool.push_back(b);
        }
    }

    for (Bullet* b : pool) {
        if (!b->IsActive()) {
            b->SetIsActive(true);
            b->SetPosition(pos);
            b->SetVelocity(vel);
            b->SetDamage(damage);

            return b;
        }
    }

    Bullet* b = GameManager::InstantiateGameObject<Bullet>(*baseBulletPrefab);
    b->SetVelocity(vel);
    b->SetDamage(damage);

    pool.push_back(b);
    poolSize++;

    return b;
}

void BulletFactory::RecycleBullet(Bullet* bullet) {
    if (bullet != nullptr)
        bullet->SetIsActive(false);
}