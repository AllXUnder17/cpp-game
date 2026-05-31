#ifndef _ENEMY_STATE_
#define _ENEMY_STATE_

class Enemy;

class EnemyState {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    virtual ~EnemyState() = default;

    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    virtual void OnUpdate(Enemy* enemy, float deltaTime) = 0;
    virtual void OnEnter(Enemy* enemy) = 0;
    virtual void OnExit(Enemy* enemy) = 0;
private:
    
};

#endif