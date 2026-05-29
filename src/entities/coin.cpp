#include "coin.h"

#include "core/managers/gamemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Coin::Coin(const EntityConfig& config) : Entity(config) { }

//===DESTRUCTOR===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
// void Coin::OnTakeDamage(unsigned damage) {
//     TraceLog(LOG_INFO, "OUCH!!!");
// }

void Coin::OnCollect() {
    TraceLog(LOG_INFO, "Collected coin!");
    GameManager::Destroy(this);
}