#ifndef _IDRAWABLE_
#define _IDRAWABLE_

#include "raylib.h"

class IDrawable {
public:
    virtual ~IDrawable() = default;

    virtual void Draw() const = 0;
};

#endif