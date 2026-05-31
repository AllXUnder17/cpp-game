#include "chasestate.h"

#include "entities/player.h"
#include "entities/characters/enemy.h"

#include "enemystatemachine.h"
#include "raymath.h"

#include "core/managers/gamemanager.h"

//===MEMBER FUNCTIONS===
void ChaseState::OnEnter(Enemy* enemy) {
    TraceLog(LOG_INFO, ("Entered Chase state on enemy " + std::to_string(enemy->GetID())).c_str());
    
    enemy->SetAnimationLayer(1);
}

void ChaseState::OnUpdate(Enemy* enemy, float deltaTime) {
    GameObject* player = GameManager::GetGameObjectWithTag("Player");

    if (player == nullptr)
        return;
    
    Vector2 playerPosition = dynamic_cast<Player*>(player)->GetPosition();

    float distanceToPlayer = Vector2Distance(enemy->GetPosition(), playerPosition);

    if (distanceToPlayer >= enemy->GetChaseRadius()) {
        enemy->GetStateMachine().ChangeState(enemy, enemy->GetIdleState());
        return;
    }
    if (distanceToPlayer <= enemy->GetAttackRadius()) {
        enemy->GetStateMachine().ChangeState(enemy, enemy->GetAttackState());
        return;
    }

    enemy->MoveTowardsLerp(playerPosition, 0.02f);
}

void ChaseState::OnExit(Enemy* enemy) { 
    TraceLog(LOG_INFO, ("Exited Chase state on enemy " + std::to_string(enemy->GetID())).c_str());
}