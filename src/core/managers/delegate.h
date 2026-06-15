#ifndef _DELEGATE_
#define _DELEGATE_

#include <functional>
#include <unordered_map>
#include <iostream> // IWYU pragma: keep

template<typename T>
class Delegate;

template<typename ReturnType, typename... Args>
class Delegate<ReturnType(Args ...)> {
public:
    using CallbackType = std::function<ReturnType(Args...)>;
    
    //===CONSTRUCTORS===
    Delegate() = default;
    
    //===DESTRUCTOR===
    ~Delegate() = default;
    
    //===OPERATORS===
    ReturnType operator()(Args... args) {
        // Structured binding works perfectly on maps out-of-the-box!
        for (auto& [id, callback] : callbacks) {
            if (callback) {
                callback(args...);
            }
        }
    }
    
    //===MEMBER FUNCTIONS===
    size_t AddListener(CallbackType callback) {
        size_t id = currId++;
        callbacks[id] = callback;
        return id;
    }

    size_t AddListener(size_t& listenerId, CallbackType callback) {
        // If the ID already exists, this safely updates/overwrites it
        while (callbacks.find(listenerId) != callbacks.end())
            listenerId++;

        callbacks[listenerId] = callback;

        return listenerId;
    }

    void Remove(const size_t& id) {
        // Instant map erasure instead of iterating through a vector search
        callbacks.erase(id);
    }

    // Clears all listeners registered to this specific delegate instances
    void Clear() {
        callbacks.clear();
    }

private:
    size_t currId = 0;
    
    // Key: listener ID | Value: The bound std::function callback
    std::unordered_map<size_t, CallbackType> callbacks;
};

#endif