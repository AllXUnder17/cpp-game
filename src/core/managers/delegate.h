#ifndef _DELEGATE_
#define _DELEGATE_

#include <functional>
#include <algorithm>
#include <iostream> // IWYU pragma: keep
#include <vector>

template<typename T>
class Delegate;

template<typename ReturnType, typename... Args>
class Delegate<ReturnType(Args ...)> {
public:
    using CallbackType = std::function<ReturnType(Args...)>;
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    Delegate() = default;
    
    //===DESTRUCTOR===
    ~Delegate() = default;
    
    //===OPERATORS===
    ReturnType operator()(Args... args) {
    for (auto& [id, callback] : callbacks) {
        callback(args ...);
    }
}
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    size_t Add(CallbackType callback) {
        size_t id = currId++;

        callbacks.push_back({id, callback});

        return id;
    }

    void Remove(const size_t& id) {
    auto it = std::find_if(callbacks.begin(), callbacks.end(), [id](const Entry& entry) {
        return id == entry.id;
    });

    if (it != callbacks.end())
        callbacks.erase(it);
}


    ReturnType Invoke(CallbackType callback);

private:
    struct Entry {
        std::size_t id = 0;
        CallbackType callback;
    };

    size_t currId = 0;

    std::vector<Entry> callbacks;
};


#endif