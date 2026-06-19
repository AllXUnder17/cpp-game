#ifndef _IONEND_
#define _IONEND_

class IOnEnd {
public:
    virtual ~IOnEnd() = default;

    virtual void OnEnd() = 0;
};

#endif