#include "deathstate.h"

#include "core/managers/gamemanager.h"

#include "entities/characters/enemy.h"

#include "enemystatemachine.h"

//===MEMBER FUNCTIONS===
void DeathState::OnEnter(Enemy* enemy) {    
    enemy->SetAnimationLayer(4);

    delegateIdx = enemy->GetOnCurrAnimEndEvent().AddListener([this, enemy]() {
        EnemyState* prevState = enemy->GetStateMachine().GetPrevState(); 

        enemy->SetIsActive(false);
        
        enemy->GetOnCurrAnimEndEvent().Remove(delegateIdx);

        OnExit(enemy);
    });
}

void DeathState::OnUpdate(Enemy* enemy, float deltaTime) { }

void DeathState::OnExit(Enemy* enemy) { 
    // delete enemy;
    GameManager::Destroy(enemy);
}