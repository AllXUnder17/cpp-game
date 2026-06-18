#ifndef _GFX_MANAGER_
#define _GFX_MANAGER_

#include <ostream> // IWYU pragma: keep
#include <vector>
#include "raylib.h"

// #include "core/idrawable.h"

class IDrawable;

class GFXManager {
public:
    //===STATIC MEMBERS===
    static Color BACKGROUND_COLOR;
    
    static unsigned short VIRTUAL_WIDTH;
    static unsigned short VIRTUAL_HEIGHT;
    
    static unsigned FRAMES_PER_SECOND;
    static float FRAME_WAIT_TIME;

    //===CONSTRUCTORS===
    GFXManager() = delete;
    
    static void Init(const unsigned animationFramesPerSecond = 12);
    
    //===DESTRUCTOR===

    //===GETTERS===
    static const Camera2D& GetCamera();

    static const RenderTexture2D& GetCanvas();
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    
    //---Drawables---
    static void HandleDrawables();

    static void AddDrawable(IDrawable* drawable);
    static void RemoveDrawable(IDrawable* drawable);

    static const std::vector<IDrawable*>& GetDrawables();
    
    //---Canvas---
    static void DrawCanvas();
    static void RenderCanvas(); 

    //---Stuff---
    static void OutputInfo(std::stringstream& ss);
private:
    static std::vector<IDrawable*> drawables;

    static Camera2D camera;
    static RenderTexture2D canvas;
};

#endif