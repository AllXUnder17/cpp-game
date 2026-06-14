#include "inputmanager.h"

#include "gamemanager.h" // IWYU pragma: keep

//===CONSTANTS===

//===STATIC MEMBERS===
std::unordered_map<KeyboardKey, std::function<void()>> InputManager::onKeyPressedCallbacks = std::unordered_map<KeyboardKey, std::function<void()>>();
std::unordered_map<KeyboardKey, std::function<void()>> InputManager::onKeyReleasedCallbacks = std::unordered_map<KeyboardKey, std::function<void()>>();

std::unordered_map<KeyboardKey, std::function<void()>> InputManager::onKeyDownCallbacks = std::unordered_map<KeyboardKey, std::function<void()>>();
std::unordered_map<KeyboardKey, std::function<void()>> InputManager::onKeyUpCallbacks = std::unordered_map<KeyboardKey, std::function<void()>>();

//===MEMBER FUNCTIONS===
void InputManager::SetKeybind(const KeyboardKey& key, std::function<void()> callback, const KeybindType& type) {
    switch (type) {
    case ON_KEY_PRESSED:
        onKeyPressedCallbacks[key] = callback;
        break;
    case ON_KEY_RELEASED:
        onKeyReleasedCallbacks[key] = callback;
        break;
    case ON_KEY_DOWN:
        onKeyDownCallbacks[key] = callback;
        break;
    case ON_KEY_UP:
        onKeyUpCallbacks[key] = callback;
        break;
    }
}

void InputManager::OnUpdate() {
    for (const auto& [key, callback] : onKeyPressedCallbacks) {
        if (IsKeyPressed(key)) {
            callback();
        }
    }

    for (const auto& [key, callback] : onKeyReleasedCallbacks) {
        if (IsKeyReleased(key)) {
            callback();
        }
    }

    for (const auto& [key, callback] : onKeyDownCallbacks) {
        if (IsKeyDown(key)) {
            callback();
        }
    }

    for (const auto& [key, callback] : onKeyUpCallbacks) {
        if (IsKeyUp(key)) {
            callback();
        }
    }
}