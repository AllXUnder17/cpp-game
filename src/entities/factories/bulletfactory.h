#ifndef _BULLET_FACTORY_
#define _BULLET_FACTORY_

#include <vector>

#include "entities/bullets/bullet.h"

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
    static Bullet* SpawnBullet(const Vector2& pos, const Vector2& vel);

    static void RecycleBullet(Bullet* bullet);
private:
    static std::vector<Bullet*> pool;

    static Bullet* baseBulletPrefab;
};

#endif