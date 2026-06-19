#ifndef _IONAWAKE_
#define _IONAWAKE_

class IOnAwake {
public:
    virtual ~IOnAwake() = default;

    virtual void OnAwake() {}
};

#endif