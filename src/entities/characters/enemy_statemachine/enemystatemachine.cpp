#include "enemystatemachine.h"

#include "entities/characters/enemy.h"
#include "enemystate.h"

#include "raylib.h"  // IWYU pragma: keep

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
EnemyState* EnemyStateMachine::GetCurrState() const {
    return currState;
}
EnemyState* EnemyStateMachine::GetPrevState() const {
    return prevState;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
void EnemyStateMachine::ChangeState(Enemy* enemy, EnemyState* newState) {
    if (newState == currState)
        return;

    //---Special states---
    if (currState == enemy->GetDeathState())
        return;

    prevState = currState;

    if (currState != nullptr)
        currState->OnExit(enemy);

    currState = newState;

    currState->OnEnter(enemy);
}

void EnemyStateMachine::OnUpdate(Enemy* enemy, float deltaTime) {
    if (currState == nullptr)
        return;

    currState->OnUpdate(enemy, deltaTime);
}