#ifndef _BULLET_FACTORY_
#define _BULLET_FACTORY_

#include <vector>

#include "entities/bullets/bullet.h"

class BulletFactory {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    BulletFactory(const size_t& capacity);
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    Bullet* SpawnBullet(const Vector2& pos, const Vector2& vel);

    void RecycleBullet(Bullet* bullet);
private:
    std::vector<Bullet*> pool;
};

#endif