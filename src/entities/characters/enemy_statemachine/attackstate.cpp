#include "attackstate.h"

#include "core/managers/gamemanager.h"

#include "entities/characters/enemy.h"
#include "enemystatemachine.h"
#include "entities/player.h"
#include "raymath.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void AttackState::OnEnter(Enemy* enemy) {
    TraceLog(LOG_INFO, ("Entered Attack state on enemy " + std::to_string(enemy->GetID())).c_str());

    elapsedAttackTime = 0.0f;

    enemy->SetAnimationLayer(2);
}

void AttackState::OnUpdate(Enemy* enemy, float deltaTime) {
    // elapsedAttackTime += deltaTime;

    // if (elapsedAttackTime >= enemy->GetAttackTime()) {
    //     enemy->OnAttack();
    //     elapsedAttackTime = 0.0f;
    // }

    GameObject* player = GameManager::GetGameObjectWithTag("Player");
    Vector2 playerPosition = dynamic_cast<Player*>(player)->GetPosition();
    float distanceToPlayer = Vector2Distance(enemy->GetPosition(), playerPosition);
    
    if (distanceToPlayer > enemy->GetAttackRadius()) {
        enemy->GetStateMachine().ChangeState(enemy, enemy->GetChaseState());
        return;
    }
}

void AttackState::OnExit(Enemy* enemy) {
    TraceLog(LOG_INFO, ("Exited Attack state on enemy " + std::to_string(enemy->GetID())).c_str());
    
}