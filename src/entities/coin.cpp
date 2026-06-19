#include "coin.h"

#include "core/managers/gamemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Coin::Coin(const EntityConfig& config) : Entity(config) { }
Coin::Coin(const Coin& other) : Entity(other) { }

//===DESTRUCTOR===

//===OPERATORS===
Coin& Coin::operator=(const Coin& other) {
    if (this == &other)
        return *this;

    Entity::operator=(other);

    return *this;
}

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===

CollectableType Coin::OnCollect() {
    // SetIsDead(true);

    GameManager::Destroy(this);

    return COIN;
}