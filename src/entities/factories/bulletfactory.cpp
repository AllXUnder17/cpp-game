#include "bulletfactory.h"
#include "core/spriteloader.h"
#include "core/spritesheet.h"

#include "core/managers/gamemanager.h"

#include <cstdlib>  // IWYU pragma: keep

//===CONSTANTS===

//===STATIC MEMBERS===
std::vector<Bullet*> BulletFactory::pool = std::vector<Bullet*>();

Bullet* BulletFactory::baseBulletPrefab = nullptr;

//===CONSTRUCTORS===
void BulletFactory::Init() {
    //---Populate pool---
    size_t poolSize = 10;

    pool.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {

        Bullet* b = GameManager::InstantiateGameObject<Bullet>(EntityConfig{
            GameObjectConfig {
                .sprite = SpriteLoader::GetSprite("bullet.png"), 
                .position = { -1000, -1000 }, 
                .isActive = false
            }, SpriteSheet::empty, Vector2{8., 8}}, 
            Vector2{0, 0}, 0);

        pool.push_back(b);
    }
}
void BulletFactory::Uninit() {
    delete baseBulletPrefab;
    baseBulletPrefab = nullptr;
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
//---Inherited---

Bullet* BulletFactory::SpawnBullet(const Vector2& pos, const Vector2& vel, unsigned damage) {
    for (Bullet* b : pool) {
        if (!b->IsActive()) {
            b->SetIsActive(true);
            b->SetPosition(pos);
            b->SetVelocity(vel);
            b->SetDamage(damage);

            return b;
        }
    }

    Bullet* b = GameManager::InstantiateGameObject<Bullet>(EntityConfig{
        GameObjectConfig{
            .sprite = SpriteLoader::GetSprite("bullet.png"),
            .position = pos,
            .isActive = true
        }, SpriteSheet::empty, Vector2{8., 8}}, vel, damage);

    pool.push_back(b);

    return b;
}

void BulletFactory::RecycleBullet(Bullet* bullet) {
    if (bullet != nullptr)
        bullet->SetIsActive(false);
}