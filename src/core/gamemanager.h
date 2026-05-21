#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include <vector>
#include <string>

#include "idrawable.h"
#include "iupdatable.h"

class GameManager {
public:
    static unsigned short WINDOW_WIDTH;
    static unsigned short WINDOW_HEIGHT;

    //---Singleton--
    static GameManager& GetInstance();
    
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    //---Workflow---
    static void InitGame(
        const unsigned short& windowWidth, 
        const unsigned short& windowHeight, 
        const std::string& windowTitle = "Game",
        const unsigned char fps = 60);
    static void UninitGame();

    static const Camera2D& GetCamera();

    //---Drawables---
    static void HandleDrawables();

    static void AddDrawable(IDrawable* drawable);
    static void RemoveDrawable(IDrawable* drawable);

    static const std::vector<IDrawable*>& GetDrawables();

    //---Updatables---
    static void HandleUpdatables();

    static void AddUpdatable(IUpdatable* updatable);
    static void RemoveUpdatable(IUpdatable* updatable);

    static const std::vector<IUpdatable*>& GetUpdatables();

private:
    // GameManager() { 
    //     drawables = std::vector<IDrawable*>(); 
    //     updatables = std::vector<IUpdatable*>();
    // };

    GameManager() = delete;

    static Camera2D camera;

    static std::vector<IDrawable*> drawables;
    static std::vector<IUpdatable*> updatables;
};

#endif