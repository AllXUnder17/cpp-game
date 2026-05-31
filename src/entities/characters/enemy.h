#ifndef _ENEMY_
#define _ENEMY_

#include "core/idamagable.h"

#include "enemy_statemachine/attackstate.h"
#include "enemy_statemachine/chasestate.h"
#include "enemy_statemachine/enemystatemachine.h"
#include "enemy_statemachine/idlestate.h"
#include "entities/character.h"

class Enemy : public Character, public IDamagable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Enemy(const EntityConfig& config, float moveSpeed, unsigned health);
    Enemy(const Enemy& other);
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    Enemy& operator=(const Enemy& other);
    
    //===GETTERS===
    float GetChaseRadius() const;
    float GetAttackRadius() const;
    float GetAttackTime() const;

    EnemyStateMachine& GetStateMachine();

    EnemyState* GetIdleState();
    EnemyState* GetChaseState();
    EnemyState* GetAttackState();
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void OnAttack();
    //---Inherited---
    void OnTakeDamage(unsigned damage) override;
    void OnUpdate() override;

private:
    unsigned currHealth;

    EnemyStateMachine stateMachine;
    
    IdleState idleState;
    ChaseState chaseState;
    AttackState attackState;
};

#endif