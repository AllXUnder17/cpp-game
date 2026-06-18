#include "scene.h"

//===CONSTANTS===

//===STATIC MEMBERS===

//===CONSTRUCTORS===
Scene::Scene(std::string name) {
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

std::string Scene::GetName() const {
    return name;
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
