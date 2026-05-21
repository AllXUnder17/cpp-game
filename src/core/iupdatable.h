#ifndef _IUPDATABLE_
#define _IUPDATABLE_

class IUpdatable {
public:
    virtual void OnUpdate() = 0;

    virtual ~IUpdatable() = default;
};

#endif