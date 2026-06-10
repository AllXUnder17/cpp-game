#include "enemy.h"

#include "core/managers/gamemanager.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Enemy::Enemy(const EntityConfig& config, float moveSpeed, unsigned health) : Character(config, moveSpeed) {
    this->currHealth = health;

    this->idleState = IdleState();
    this->chaseState = ChaseState();
    this->attackState = AttackState();

    stateMachine.ChangeState(this, &idleState);
}

Enemy::Enemy(const Enemy& other) : Character(other) {
    this->currHealth = other.currHealth;

    this->idleState = IdleState();
    this->chaseState = ChaseState();
    this->attackState = AttackState();

    stateMachine.ChangeState(this, &idleState);
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
float Enemy::GetAttackRadius() const {
    return 25;
}
float Enemy::GetChaseRadius() const {
    return 100;
}
float Enemy::GetAttackTime() const {
    return 0.5;
}

EnemyStateMachine& Enemy::GetStateMachine() {
    return stateMachine;
}

EnemyState* Enemy::GetIdleState() {
    return &idleState;
}
EnemyState* Enemy::GetChaseState() {
    return &chaseState;
}
EnemyState* Enemy::GetAttackState() {
    return &attackState;
}
EnemyState* Enemy::GetDeathState() {
    return  &deathState;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
void Enemy::OnUpdate() {
    Character::OnUpdate();

    stateMachine.OnUpdate(this, GetFrameTime());
}

void Enemy::OnTakeDamage(unsigned damage) {
    currHealth -= damage;

    if (currHealth <= 0) {
        this->stateMachine.ChangeState(this, GetDeathState());
    }
}