#include "deathstate.h"

#include "core/managers/gamemanager.h"

#include "entities/characters/enemy.h"

#include "enemystatemachine.h"

//===MEMBER FUNCTIONS===
void DeathState::OnEnter(Enemy* enemy) {    
    enemy->SetAnimationLayer(4);
}

void DeathState::OnUpdate(Enemy* enemy, float deltaTime) {
    if (enemy->GetCurrFrameIdx() == enemy->GetCurrAnimLayerLength() - 1)
        OnExit(enemy);
}

void DeathState::OnExit(Enemy* enemy) { 
    GameManager::Destroy(enemy);
}