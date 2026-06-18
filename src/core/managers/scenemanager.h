#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include <vector>

#include "core/scene.h"

class SceneManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    static Scene* activeScene;

    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    static Scene* GetActiveScene();

    static const std::vector<Scene*>& GetBuildScenes();
    static const std::vector<Scene*>& GetLoadedScenes();
    
    static std::vector<GameObject*> GetLoadedGameObjects();
    static std::vector<GameObject*> GetActiveGameObjects();

    //===SETTERS===
    static void SetActiveScene(Scene* scene);
    
    //===MEMBER FUNCTIONS===
    static void Update();

    static void LoadScene(unsigned sceneId);
    static void LoadScene(const std::string& sceneName);

    static void AddBuildScene(Scene* scene);

    static void ClearDeadSceneReferences();
private:
    static std::vector<Scene*> buildScenes;

    static std::vector<Scene*> loadedScenes;
};

#endif