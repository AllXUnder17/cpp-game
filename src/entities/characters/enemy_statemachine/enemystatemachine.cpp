#include "enemystatemachine.h"

#include "enemystate.h"

#include "raylib.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void EnemyStateMachine::ChangeState(Enemy* enemy, EnemyState* newState) {
    if (newState == currState) {
        return;
    }

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