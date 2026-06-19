#ifndef _IONDESTROY_
#define _IONDESTROY_

class IOnDestroy {
public:
    virtual ~IOnDestroy() = default;

    virtual void OnDestroy() {}
};

#endif