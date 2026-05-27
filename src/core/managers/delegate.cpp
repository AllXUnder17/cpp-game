#include "delegate.h"

#include <algorithm>

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===
template<typename ... Args>
void Delegate<Args ...>::operator()(Args... args) {
    for (auto& [id, callback] : callbacks) {
        callback(args ...);
    }
}

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
template<typename ... Args>
size_t Delegate<Args ...>::Add(std::function<void(Args ...)> callback) {
    size_t id = currId++;

    callbacks.push_back({id, callback});

    return id;
}

template<typename ... Args>
void Delegate<Args ...>::Remove(const size_t& id) {
    auto it = std::find_if(callbacks.begin(), callbacks.end(), [id](const Entry& entry) {
        return id == entry.id;
    });

    if (it != callbacks.end())
        callbacks.erase(it);
}