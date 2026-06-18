#include "scenemanager.h"

#include <algorithm>

//===CONSTANTS===

//===STATIC MEMBERS===
Scene* SceneManager::activeScene = nullptr;

std::vector<Scene*> SceneManager::buildScenes = std::vector<Scene*>();
std::vector<Scene*> SceneManager::loadedScenes = std::vector<Scene*>();

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
Scene* SceneManager::GetActiveScene() {
    return activeScene;
}

const std::vector<Scene*>& SceneManager::GetBuildScenes() {
    return buildScenes;
}

const std::vector<Scene*>& SceneManager::GetLoadedScenes() {
    return loadedScenes;
}

std::vector<GameObject*> SceneManager::GetLoadedGameObjects() {
    std::vector<GameObject*> loadedGameobjects;

    for (auto& sc : loadedScenes) {
        for (auto gameObject : sc->GetGameObjects()){
            loadedGameobjects.push_back(gameObject);
        }
    }

    return loadedGameobjects;
}

// std::vector<GameObject*> SceneManager::GetActiveGameObjects() {
    
// }

//===SETTERS===
void SceneManager::SetActiveScene(Scene* scene) {
    activeScene = scene;
}

//===MEMBER FUNCTIONS===
void SceneManager::Update() {
    for (auto sc : loadedScenes) {
        sc->Update();
    }
}

void SceneManager::LoadScene(const std::string& name) {
    auto it = std::find_if(buildScenes.begin(), buildScenes.end(), [name](Scene* sc){return sc->GetName() == name;});

    if (it == buildScenes.end()) {
        TraceLog(LOG_WARNING, "da");
        return;
    }

    (*it)->Load();
    loadedScenes.push_back(*it);
}

void SceneManager::AddBuildScene(Scene* scene) {
    buildScenes.push_back(scene);
}

void SceneManager::ClearDeadSceneReferences() {
    for (auto& sc : loadedScenes) {
        // Access the scene's actual internal vector by reference
        auto& sceneObjects = sc->GetGameObjects(); 
        
        for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ) {
            if ((*it)->GetIsDead()) {
                it = sceneObjects.erase(it); // Safe erasure on the TRUE container
            } else {
                ++it;
            }
        }
    }
}