#ifndef _IDRAWABLE_
#define _IDRAWABLE_

class IDrawable {
public:
    virtual ~IDrawable() = default;

    virtual void Draw() = 0;
};

#endif