#include "onhitstate.h"

#include "entities/characters/enemy.h"

//===MEMBER FUNCTIONS===
void OnHitState::OnEnter(Enemy* enemy) {
    enemy->SetAnimationLayer(3);
}

void OnHitState::OnUpdate(Enemy* enemy, float deltaTime) {
    if (enemy->GetCurrFrameIdx() >= enemy->GetCurrAnimLayerLength() - 1)
        OnExit(enemy);
}

void OnHitState::OnExit(Enemy* enemy) {
    EnemyState* prevState = enemy->GetStateMachine().GetPrevState();
    enemy->GetStateMachine().ChangeState(enemy, prevState);
}