#ifndef _IDRAWABLE_
#define _IDRAWABLE_

#include "managers/gfxmanager.h"

class IDrawable {
public:
    virtual ~IDrawable() = default;

    virtual bool IsDrawableActive() = 0;

    virtual void Draw() = 0;
};

#endif