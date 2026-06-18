#ifndef _IDRAWABLE_
#define _IDRAWABLE_

#include "managers/gfxmanager.h"

class IDrawable {
public:
    IDrawable() {
        GFXManager::AddDrawable(this);
    }
    virtual ~IDrawable() {
        GFXManager::RemoveDrawable(this);
    }

    virtual bool IsDrawableActive() = 0;

    virtual void Draw() = 0;
};

#endif