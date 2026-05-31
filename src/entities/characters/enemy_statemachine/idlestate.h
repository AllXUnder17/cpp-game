#ifndef _IDLE_STATE_
#define _IDLE_STATE_

#include "enemystate.h"

class IdleState : public EnemyState{
public:
    //===MEMBER FUNCTIONS===
    void OnUpdate(Enemy* enemy, float deltaTime) override;
    void OnEnter(Enemy* enemy) override;
    void OnExit(Enemy* enemy) override;
private:
    
};

#endif