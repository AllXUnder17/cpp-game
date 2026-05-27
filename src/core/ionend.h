#ifndef _IONEND_
#define _IONEND_

#include <iostream>

class IOnEnd {
public:
    ~IOnEnd() = default;

    virtual void OnEnd() = 0;
};

#endif