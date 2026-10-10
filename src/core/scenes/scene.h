#ifndef _SCENE_
#define _SCENE_

#include <memory>
#include <vector>
#include <string>

#include "raylib.h"
#include "core/gameobject.h"

class Scene {
public:
    //===CONSTRUCTORS & DESTRUCTOR===
    Scene(const std::string& name);
    virtual ~Scene() = default; 

    //===GETTERS===
    const std::string& GetName() const;
    
    //===MEMBER FUNCTIONS===
    virtual void OnLoad() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnUnload();

    void AddGameObject(GameObject* go);

protected:
    std::vector<std::unique_ptr<GameObject>> gameobjects;
    std::string name;
};

inline Scene::Scene(const std::string& name) : name(name) {}


inline const std::string& Scene::GetName() const {
    return name;
}

inline void Scene::OnUnload() {
    gameobjects.clear(); 
}

inline void Scene::OnUpdate(float deltaTime) {
    for (const auto& go : gameobjects) {
        if (go) go->OnUpdate();
    }
}

inline void Scene::AddGameObject(GameObject* go) {
    if (go == nullptr)
        return;

    gameobjects.push_back(std::unique_ptr<GameObject>(go));

    TraceLog(LOG_INFO, "SCENE: Added gameobject %s to scene %s", go->GetName(), name.c_str());
    TraceLog(LOG_INFO, "SCENE: Current gameobjects in scene %s: %d", name.c_str(), gameobjects.size());
}

#endif