#ifndef _IONSTART_
#define _IONSTART_

class IOnStart {
public:
    virtual ~IOnStart() = default;

    virtual void OnStart() = 0; 
};

#endif