#ifndef _FACTORY_
#define _FACTORY_

#include <iostream>

class Factory {
public:
    //===MEMBER FUNCTIONS===
    virtual void Init() = 0;
    virtual void OnUpdate() = 0;
private:
    
};

#endif