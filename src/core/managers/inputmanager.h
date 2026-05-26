#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#include <functional>
#include <unordered_map>

#include "core/iupdatable.h"
#include "raylib.h"

enum KeybindType {
    ON_KEY_PRESSED,
    ON_KEY_RELEASED,
    ON_KEY_UP,
    ON_KEY_DOWN
};

class InputManager : public IUpdatable {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    static InputManager& GetInstance();
    
    //===CONSTRUCTORS===
    InputManager(const InputManager&) = delete;
    void operator=(const InputManager&) = delete;

    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    void SetKeybind(const KeyboardKey& key, std::function<void()> callback, const KeybindType& type);
    
    //===MEMBER FUNCTIONS===
    void OnUpdate() override;

private:
    InputManager(); 
    ~InputManager() = default;

    static std::unordered_map<KeyboardKey, std::function<void()>> onKeyPressedCallbacks;
    static std::unordered_map<KeyboardKey, std::function<void()>> onKeyReleasedCallbacks;

    static std::unordered_map<KeyboardKey, std::function<void()>> onKeyDownCallbacks;
    static std::unordered_map<KeyboardKey, std::function<void()>> onKeyUpCallbacks;
};

#endif