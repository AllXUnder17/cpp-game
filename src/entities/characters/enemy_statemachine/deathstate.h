#ifndef _DEATH_STATE_
#define _DEATH_STATE_

#include <cstddef>

#include "enemystate.h"

class DeathState : public EnemyState {
public:
    //===MEMBER FUNCTIONS===
    void OnUpdate(Enemy* enemy, float deltaTime) override;
    void OnEnter(Enemy* enemy) override;
    void OnExit(Enemy* enemy) override;
private:
    size_t delegateIdx;
};

#endif