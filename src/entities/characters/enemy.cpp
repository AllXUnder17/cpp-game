#include "enemy.h"

#include "core/managers/gamemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Enemy::Enemy(const EntityConfig& config, float moveSpeed, unsigned health) : Character(config, moveSpeed){
    this->currHealth = health;
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void Enemy::OnTakeDamage(unsigned damage) {
    currHealth -= damage;
    TraceLog(LOG_INFO, ("Ouch!!! Curr Health: " + std::to_string(currHealth)).c_str());

    if (currHealth <= 0) {
        TraceLog(LOG_INFO, "Enemy dead!");
        GameManager::Destroy(this);
    }
}