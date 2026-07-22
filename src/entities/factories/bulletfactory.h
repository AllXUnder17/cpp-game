#ifndef _BULLET_FACTORY_
#define _BULLET_FACTORY_

#include <vector>

#include "core/factory.h"

#include "entities/bullets/bullet.h"

//tova shte stane na ProjectilesFactory
class BulletFactory {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    BulletFactory() = delete;
    static void Init();
    
    //===DESTRUCTOR===
    static void Uninit();
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static Bullet* SpawnBullet(const Vector2& pos, const Vector2& vel, unsigned damage);

    static void RecycleBullet(Bullet* bullet);
private:
    static std::vector<Bullet*> pool;

    static Bullet* baseBulletPrefab;

    static void InitPrefabs();
};

#endif