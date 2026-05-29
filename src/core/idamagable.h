#ifndef _IDAMAGABLE_
#define _IDAMAGABLE_

class IDamagable {
public:
    ~IDamagable() = default;

    //virtual unsigned short& GetHealth();

    virtual void OnTakeDamage(unsigned damage) = 0;
};

#endif