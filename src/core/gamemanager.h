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

    //---Drawables---
    void HandleDrawables() const;

    void AddDrawable(IDrawable* drawable);
    void RemoveDrawable(IDrawable* drawable);

    const std::vector<IDrawable*>& GetDrawables() const;

    //---Updatables---
    void HandleUpdatables() const;

    void AddUpdatable(IUpdatable* updatable);
    void RemoveUpdatable(IUpdatable* updatable);

    const std::vector<IUpdatable*>& GetUpdatables() const;

private:
    GameManager() { 
        drawables = std::vector<IDrawable*>(); 
        updatables = std::vector<IUpdatable*>();
    };

    std::vector<IDrawable*> drawables;
    std::vector<IUpdatable*> updatables;
};

#endif