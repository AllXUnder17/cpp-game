#ifndef _ATTACK_STATE_
#define _ATTACK_STATE_

#include "enemystate.h"

class AttackState : public EnemyState {
public:
    //===MEMBER FUNCTIONS===
    void OnUpdate(Enemy* enemy, float deltaTime) override;
    void OnEnter(Enemy* enemy) override;
    void OnExit(Enemy* enemy) override;
private:
    float elapsedAttackTime;
};

#endif