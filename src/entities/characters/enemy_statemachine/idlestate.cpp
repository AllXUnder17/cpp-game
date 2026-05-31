#include "idlestate.h"

#include "entities/player.h"
#include "entities/characters/enemy.h"

#include "enemystatemachine.h"
#include "raymath.h"

#include "core/managers/gamemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void IdleState::OnEnter(Enemy* enemy) {
    TraceLog(LOG_INFO, ("Entered Idle state on enemy " + std::to_string(enemy->GetID())).c_str());\
    enemy->SetAnimationLayer(0);
}

void IdleState::OnUpdate(Enemy* enemy, float deltaTime) {
    GameObject* player = GameManager::GetGameObjectWithTag("Player");

    if (player == nullptr)
        return;
    
    Vector2 playerPosition = dynamic_cast<Player*>(player)->GetPosition();

    float distanceToPlayer = Vector2Distance(enemy->GetPosition(), playerPosition);

    if (distanceToPlayer <= enemy->GetChaseRadius()) {
        enemy->GetStateMachine().ChangeState(enemy, enemy->GetChaseState());
        return;
    }
}

void IdleState::OnExit(Enemy* enemy) { 
    TraceLog(LOG_INFO, ("Exited Idle state on enemy " + std::to_string(enemy->GetID())).c_str());
}