#include "gamemanager.h"

#include "core/managers/inputmanager.h"

#include "core/spriteloader.h"
#include "core/audioloader.h"

#include "entities/factories/bulletfactory.h"
#include "entities/factories/collectablefactory.h"
#include "entities/factories/enemyfactory.h"

#include <algorithm>
#include <iomanip> // IWYU pragma: keep

unsigned short GameManager::WINDOW_WIDTH = 1280;
unsigned short GameManager::WINDOW_HEIGHT = 720;

std::vector<DelayedCallback> GameManager::delayedCallbacks = std::vector<DelayedCallback>();

void GameManager::InitGame(
        const unsigned short windowWidth, 
        const unsigned short windowHeight, 
        const std::string& windowTitle,
        const unsigned char fps) {
    GameManager::WINDOW_WIDTH = windowWidth;
    GameManager::WINDOW_HEIGHT = windowHeight;

    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    //ToggleFullscreen();
    
    SetTargetFPS(fps);
    
    //build all scenes

    GFXManager::Init();
    //AudioLoader::Init();
    PhysicsManager::Init();

    //---INIT FACTORIES---
    BulletFactory::Init();
    CollectableFactory::Init(2);
    EnemyFactory::Init();

    HandleOnStart();
}

void GameManager::UninitGame() {
    //unload all current scenes

    SpriteLoader::UnloadAll();
    //AudioLoader::UnloadAll();

    HandleOnEnd();

    BulletFactory::Uninit();
    EnemyFactory::Uninit();
    CollectableFactory::Uninit();

    CloseWindow();
}

//---Others---

void GameManager::Destroy(GameObject* go) {
    if (go == nullptr) return;

    go->OnDestroy();

    go->SetIsDead(true);
}

void GameManager::HandleUpdate() {
    InputManager::OnUpdate();
    PhysicsManager::UpdateCollision();

    HandleDelayedCallbacks();

    //CollectableFactory::OnUpdate(GetFrameTime());

    SceneManager::Update();

    CleanupDeadObjects();
}

void GameManager::CleanupDeadObjects() {
    auto loadedGameObjects = SceneManager::GetLoadedGameObjects();

    for (auto go : loadedGameObjects) {
        if (go && go->GetIsDead()) {
            TraceLog(LOG_INFO, "Deleted object: %p", go);
            
            delete go;
        }
    }

    // 3. Tell your scenes to scrub the now-deleted pointers out of their vectors
    SceneManager::ClearDeadSceneReferences();
}

void GameManager::OutputInfo(std::stringstream& ss) {
    // ss << std::fixed << "GM: [\tALL_CNT: " << gameObjects.size() << ",\t"
    //     << "ACTIVE_CNT: " << std::count_if(gameObjects.begin(), gameObjects.end(), [](const auto& pair){return pair.second->IsActive();}) << " ]\n\n";
}

void GameManager::HandleOnStart() {

}

void GameManager::HandleOnEnd() {

}

GameObject* GameManager::GetGameObjectWithTag(const std::string& tag) {
    auto gameObjects = SceneManager::GetActiveScene()->GetGameObjects();
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [tag](const auto& go) { return go->GetTag() == tag;});

    if (it == gameObjects.end())
        return nullptr;

    return *it;
}

void GameManager::Invoke(std::function<void()> callback, float delay,bool isRepeated) {
    delayedCallbacks.push_back({callback, delay, 0, isRepeated});
}

void GameManager::HandleDelayedCallbacks() {
    float deltaTime = GetFrameTime();

    // 1. Create a snapshot copy of the list of callbacks to iterate through.
    // This isolates the loops from any new callbacks pushed inside item.callback()!
    auto callbacksCopy = delayedCallbacks;
    delayedCallbacks.clear(); // Empty the master list to accept new additions cleanly

    // 2. Loop forward through your safe snapshot
    for (size_t i = 0; i < callbacksCopy.size(); ++i) {
        auto& item = callbacksCopy.at(i);
        item.elapsedTime += deltaTime;

        if (item.elapsedTime >= item.delay) {
            item.callback(); // Entirely safe if this adds items to 'delayedCallbacks'!

            if (item.isRepeated) {
                item.elapsedTime = 0.0f;
                delayedCallbacks.push_back(item); // Re-add it to the main queue
            }
            // If it's not repeated, we simply let it drop here (no erase needed!)
        } else {
            // Timer didn't finish, keep it alive by transferring back to main queue
            delayedCallbacks.push_back(item);
        }
    }
}