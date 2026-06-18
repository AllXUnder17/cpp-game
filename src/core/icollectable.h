#ifndef _ICOLLECTABLE_
#define _ICOLLECTABLE_

enum CollectableType {
    COIN, KEY, AMMO
};

class ICollectable {
public:
    ICollectable() = default;
    virtual ~ICollectable() = default;

    virtual CollectableType OnCollect() = 0;
};

#endif