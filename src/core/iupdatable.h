#ifndef _IUPDATABLE_
#define _IUPDATABLE_

class IUpdatable {
public:
    virtual ~IUpdatable() = default;

    virtual void OnUpdate() = 0;
};

#endif