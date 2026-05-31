#ifndef _ENEMYSM_
#define _ENEMYSM_

class EnemyState;
class Enemy;

class EnemyStateMachine {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    EnemyStateMachine() = default;
    EnemyStateMachine(const EnemyStateMachine& other) = delete;
    
    //===DESTRUCTOR===
    ~EnemyStateMachine() = default;
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void OnUpdate(Enemy* enemy, float deltaTime);
    void ChangeState(Enemy* enemy, EnemyState* newState);
private:

    EnemyState* currState = nullptr;
};

#endif