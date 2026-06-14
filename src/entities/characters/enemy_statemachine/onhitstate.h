#ifndef _ONHIT_STATE_
#define _ONHIT_STATE_

#include <cstddef>

#include "enemystate.h"

class OnHitState : public EnemyState {
public:    
    //===MEMBER FUNCTIONS===
    void OnEnter(Enemy* enemy) override;
    void OnUpdate(Enemy* enemy, float deltaTime) override;
    void OnExit(Enemy* enemy) override;
private:
    size_t delegateIdx;
};

#endif