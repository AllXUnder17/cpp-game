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
    EnemyState* GetPrevState() const;
    EnemyState* GetCurrState() const;
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    void OnUpdate(Enemy* enemy, float deltaTime);
    void ChangeState(Enemy* enemy, EnemyState* newState);
private:
    EnemyState* prevState = nullptr;
    EnemyState* currState = nullptr;
};

#endif