#include "bulletfactory.h"
#include "core/spriteloader.h"
#include "core/spritesheet.h"
#include <cstdlib>  // IWYU pragma: keep

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
BulletFactory::BulletFactory(const size_t& capacity) {

    pool.reserve(capacity);

    for (size_t i = 0; i < capacity; i++) {
        Bullet* b = new Bullet(
            { 
                .sprite = SpriteLoader::GetSprite("bullet.png"), 
                .position = { -1000, -1000 }, 
                .isActive = false
            },
            //SpriteSheet(SpriteLoader::GetSprite("bullet.png"), 16, 16, {1}),
            SpriteSheet::empty,
            {0, 0});
        
        pool.push_back(b);
    }
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
Bullet* BulletFactory::SpawnBullet(const Vector2& pos, const Vector2& vel) {
    for (Bullet* b : pool) {
        if (!b->IsActive()) {
            b->SetIsActive(true);
            b->SetPosition(pos);
            b->SetVelocity(vel);

            return b;
        }
    }

    Bullet* b = new Bullet({
        .sprite = SpriteLoader::GetSprite("bullet.png"),
        .position = pos,
        .isActive = true
    }, SpriteSheet::empty, 
    vel);

    pool.push_back(b);

    return b;
}

void BulletFactory::RecycleBullet(Bullet* bullet) {
    if (bullet != nullptr)
        bullet->SetIsActive(false);
}