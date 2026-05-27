#ifndef _DELEGATE_
#define _DELEGATE_

#include <functional>
#include <iostream> // IWYU pragma: keep
#include <vector>

template<typename... Args>
class Delegate {
public:

    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Delegate() = default;
    
    //===DESTRUCTOR===
    ~Delegate() = default;
    
    //===OPERATORS===
    void operator()(Args ...);
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    size_t Add(std::function<void(Args ...)> callback);
    void Remove(const size_t& id);

private:
    struct Entry {
        std::size_t id = 0;
        std::function<void(Args ...)> callback;
    };

    size_t currId = 0;

    std::vector<Entry> callbacks;
};

#endif