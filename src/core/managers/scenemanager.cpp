#include "scenemanager.h"

#include <exception>
#include <bits/stdc++.h>
#include <algorithm>
#include <stdexcept>

#include "core/scenes/sc_main.h"
#include "core/scenes/sctest.h"
#include "core/scenes/sctest0.h"

//===CONSTANTS===

//===STATIC MEMBERS===
std::unordered_map<std::string, Scene*> SceneManager::scenes = std::unordered_map<std::string, Scene*>();

Scene* SceneManager::mainScene = nullptr;
Scene* SceneManager::loadedScene = nullptr;

//===GETTERS===
Scene* SceneManager::GetLoadedScene() {
    return loadedScene;
}

Scene* SceneManager::GetMainScene() {
    return mainScene;
}

//===SETTERS===

//===MEMBER FUNCTIONS===
//>---Private---
void SceneManager::BuildScenes() {
    mainScene = new SC_Main("Main");

    scenes["Main"] = mainScene;
    scenes["Test"] = new SCTest("Test");
    scenes["Test0"] = new SCTest0("Test0");
}

//>---Public---
void SceneManager::Init() {
    BuildScenes();

    mainScene->OnLoad();
}

void SceneManager::Uninit() {
    for (auto& [name, scene] : scenes) {
        if (scene) {
            scene->OnUnload();
            delete scene;
        }
    }

    scenes.clear();

    loadedScene = nullptr;
    mainScene = nullptr;
}

void SceneManager::LoadScene(const std::string& name) {

    auto it = scenes.find(name);
    if (it == scenes.end() || it->second == nullptr)
        throw std::runtime_error("SCENE: Scene " + name + " not found!");

    Scene* targScene = it->second;

    if (loadedScene != nullptr)
        loadedScene->OnUnload();

    loadedScene = targScene;
    loadedScene->OnLoad();

    TraceLog(LOG_INFO, "SCENE: Scene %s loaded", name.c_str());
}

void SceneManager::UnloadScene(const std::string& name) {
    Scene* targScene = scenes.find(name)->second;
    
    if (targScene == nullptr)
        return;

    targScene->OnUnload();

    targScene = nullptr;    
}

void SceneManager::Update() {
    float deltaTime = GetFrameTime();
    
    mainScene->OnUpdate(deltaTime);

    if (loadedScene != nullptr)
        loadedScene->OnUpdate(deltaTime);
}