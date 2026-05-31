#include "gamemanager.h"

#include "core/managers/inputmanager.h"

#include "core\spriteloader.h"
#include "core/audioloader.h"

#include "entities/factories/bulletfactory.h"
#include "entities/factories/collectablefactory.h"
#include "entities/factories/enemyfactory.h"

#include <algorithm>
#include <iomanip> // IWYU pragma: keep

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

std::vector<IUpdatable*> GameManager::updatables = std::vector<IUpdatable*>();
std::vector<IOnStart*> GameManager::onStartObjects = std::vector<IOnStart*>();
std::vector<IOnEnd*> GameManager::onEndObjects = std::vector<IOnEnd*>();

std::unordered_map<std::size_t, GameObject*> GameManager::gameObjects = std::unordered_map<size_t, GameObject*>();

void GameManager::InitGame(
        const unsigned short windowWidth, 
        const unsigned short windowHeight, 
        const std::string& windowTitle,
        const unsigned char fps) {
    GameManager::WINDOW_WIDTH = windowWidth;
    GameManager::WINDOW_HEIGHT = windowHeight;
    
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    
    SetTargetFPS(fps);

    // gameObjects.reserve(100);
    
    GFXManager::Init();
    AudioLoader::Init();

    //---INIT FACTORIES---
    BulletFactory::Init();
    CollectableFactory::Init();
    EnemyFactory::Init();

    HandleOnStart();
}

void GameManager::UninitGame() {
    for (auto& go : gameObjects) {
        delete go.second;
    }

    SpriteLoader::UnloadAll();
    //AudioLoader::UnloadAll();

    HandleOnEnd();

    gameObjects.clear();

    CloseWindow();
}

void GameManager::AddGameObject(GameObject* gameObject) {
    if (gameObject == nullptr) {
        return;
    }

    gameObjects[gameObject->GetID()] = gameObject;
}

void GameManager::Destroy(GameObject* gameObject) {
    GFXManager::RemoveDrawable(gameObject);

    ICollidable* collidable = dynamic_cast<ICollidable*>(gameObject);
    if (collidable != nullptr)
        CollisionManager::RemoveCollidable(collidable);

    RemoveUpdatable(gameObject);

    gameObjects.erase(gameObject->GetID());
}

const std::unordered_map<std::size_t, GameObject*>& GameManager::GetGameObjects() {
    return gameObjects;
}

//---Updatables---

void GameManager::HandleUpdatables() {
    InputManager::OnUpdate();
    CollisionManager::OnUpdate();

    for (IUpdatable* updatable : GameManager::GetUpdatables()) {
        updatable->OnUpdate();
    }
}

void GameManager::AddUpdatable(IUpdatable* updatable) {
    if (updatable == nullptr) {
        TraceLog(LOG_INFO, "const char *text, ...");
        return;
    }
    
    updatables.push_back(updatable);
}

void GameManager::RemoveUpdatable(IUpdatable* updatable) {
    auto it = std::find(updatables.begin(), updatables.end(), updatable);
    if (it != updatables.end()) {
        updatables.erase(it);
    }
}

const std::vector<IUpdatable*>& GameManager::GetUpdatables() {
    return updatables; 
}

//---Others---
void GameManager::OutputInfo(std::stringstream& ss) {
    ss << std::fixed << "GM: [\tALL_CNT: " << gameObjects.size() << ",\t"
        << "ACTIVE_CNT: " << std::count_if(gameObjects.begin(), gameObjects.end(), [](const auto& pair){return pair.second->IsActive();}) << " ]\n\n";
}

void GameManager::HandleOnStart() {
    for (auto it : onStartObjects) {
        it->OnStart();
    }
}

void GameManager::HandleOnEnd() {
    for (auto it : onEndObjects) {
        it->OnEnd();
    }
}

GameObject* GameManager::GetGameObjectWithTag(const std::string& tag) {
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [tag](const auto& pair) { return pair.second->GetTag() == tag;});

    if (it != gameObjects.end())
        return it->second;

    return nullptr;
}