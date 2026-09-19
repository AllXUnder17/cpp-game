#include "scene.h"

#include <fstream>

#include "../dependencies/nlohmann/json.hpp"
#include "entities/entity.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Scene::Scene(const std::string& name) {
    this->name = name;

    gameObjects.reserve(10);
    updatables.reserve(10);
}

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===
std::vector<GameObject*>& Scene::GetGameObjects() {
    return gameObjects;
}
std::vector<IUpdatable*>& Scene::GetUpdatables() {
    return updatables;
}

const std::string& Scene::GetName() const {
    return name;
}

const std::string Scene::GetFilePath() const {
    return "../assets/scenes/" + name + ".json";
}

//===SETTERS===

//===MEMBER FUNCTIONS===
void Scene::AddGameObject(GameObject* gameObject) {
    if (gameObject == nullptr) {
        return;
    }

    updatables.push_back(gameObject);

    gameObjects.push_back(gameObject);
}

//---Workflow---
void Scene::Load() {
    //instantiates all gameObjects
}
void Scene::Unload() {
    //destroys all gameobjects
}
void Scene::Update() {
    for (auto& go : gameObjects) {
        go->OnUpdate();
    }
}

//---File IO---
void Scene::SaveToFile() {
    TraceLog(LOG_INFO, "[SCENE] Saving scene %s to file %s.json", name.c_str(), name.c_str());

    using json = nlohmann::json;
    json data;

    for (auto go : gameObjects) {
        try {
            json goData;

            if (go->GetObjectType() == "gameobject") {
                TraceLog(LOG_INFO, "[SCENE] Saving object \"%s\" of type <GameObject>", go->GetName().c_str());
                goData = {
                    {"name", go->GetName() },
                    {"objtype", go->GetObjectType() },
                    {"sprite", go->GetSprite() == nullptr ?  "-" : go->GetSprite()->name},
                    {"pos", { go->GetPosition().x, go->GetPosition().y} }
                };
            }
            if (go->GetObjectType() == "entity") {
                TraceLog(LOG_INFO, "[SCENE] Saving object \"%s\" of type <Entity>", go->GetName().c_str());
                Entity* ent = dynamic_cast<Entity*>(go);

                goData.push_back({
                {"spritesheet", ent->GetSpriteSheet().GetSpriteSheet() == nullptr ? "-" : ent->GetSpriteSheet().GetSpriteSheet()->name },
                });
            }

            data[std::to_string(go->GetID())] = goData;
        } catch (const std::exception& e) {
            TraceLog(LOG_WARNING, "[SCENE] %s", e.what());
        }
        
    }

    std::ofstream fs = std::ofstream(("../assets/scenes/" + name + ".json").c_str());
    fs << data.dump(4);

}

void Scene::LoadFromFile() {
    TraceLog(LOG_INFO, "[SCENE] Loading scene %s from file \"%s\"", name.c_str(), GetFilePath().c_str());

    using json = nlohmann::json;
    
    std::ifstream ifs(GetFilePath());
    if (!ifs.is_open()) {
        TraceLog(LOG_ERROR, "[SCENE] Failed to open scene file: %s", GetFilePath().c_str());
        return;
    }   
    
    try {
        json data = json::parse(ifs);

        for (auto& [key, goData] : data.items()) {
            // std::string objtype = goData.at("objtype");
            // std::string objname = goData.at("name");

            std::string objtype = goData.value("objtype", "gameobject");
            std::string objname = goData.value("name", "Unnamed");

            TraceLog(LOG_INFO, "Loading object %s of type <%s>", objname.c_str(), objtype.c_str());
        }
    } catch (const nlohmann::json::parse_error& e) {
        TraceLog(LOG_ERROR, "[SCENE] Parse error in %s: %s", GetFilePath().c_str(), e.what());
        return;
    }
}