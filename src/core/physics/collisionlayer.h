#ifndef _COLLISION_LAYER_
#define _COLLISION_LAYER_

enum CollisionLayer : unsigned {
    NONE = 0,
    DEFAULT = 1 << 0,
    PLAYER = 1 << 1,
    ENEMY = 1 << 2,
    PLAYER_PROJECTILE = 1 << 3,
    ENEMY_PROJECTILE = 1 << 4,
    COLLECTABLE = 1 << 5
};

#endif