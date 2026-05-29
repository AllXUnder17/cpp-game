#ifndef _ICOLLECTABLE_
#define _ICOLLECTABLE_

class ICollectable {
public:
    ICollectable() = default;

    virtual void OnCollect() = 0;
};

#endif