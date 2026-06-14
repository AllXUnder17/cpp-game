#include "onhitstate.h"

#include "entities/characters/enemy.h"

//===MEMBER FUNCTIONS===
void OnHitState::OnEnter(Enemy* enemy) {
    enemy->SetAnimationLayer(3);

    delegateIdx = enemy->GetOnCurrAnimEndEvent().AddListener([this, enemy]() {
        EnemyState* prevState = enemy->GetStateMachine().GetPrevState();

        if (prevState) {
            enemy->GetStateMachine().ChangeState(enemy, prevState);
        }

        enemy->GetOnCurrAnimEndEvent().Remove(delegateIdx);
    });
}

void OnHitState::OnUpdate(Enemy* enemy, float deltaTime) { }

void OnHitState::OnExit(Enemy* enemy) { }