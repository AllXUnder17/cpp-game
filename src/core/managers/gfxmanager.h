#ifndef _GFX_MANAGER_
#define _GFX_MANAGER_

#include <vector>
#include "raylib.h"

#include "core/idrawable.h"

class GFXManager {
public:
    static Color BACKGROUND_COLOR;

    static unsigned short VIRTUAL_WIDTH;
    static unsigned short VIRTUAL_HEIGHT;

    //===CONSTRUCTORS===
    static void Init();
    
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
private:
    static std::vector<IDrawable*> drawables;

    static Camera2D camera;
    static RenderTexture2D canvas;
};

#endif