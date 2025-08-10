
#ifndef Scene_H
#define Scene_H

#include "SDL2/SDL.h"

class Scene
{
private:
    /* data */
public:
    Scene() = default;
    virtual ~Scene()  = default;

    virtual void init()  = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event* e) = 0;
};
#endif /* Scene_H */