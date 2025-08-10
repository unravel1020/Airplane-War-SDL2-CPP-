#ifndef SceneMain_h
#define SceneMain_h

#include "Scene.h"

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();
    
    void update() override;
    void render() override;
    void handleEvent(SDL_Event* event) override;
    void init() override;
    void clean() override;
    
    void touchBegan(float x, float y);
    void touchMoved(float x, float y);
    void touchEnded(float x, float y);
    
private:
    int m_score;
    int m_lives;
    int m_level;
};

#endif /* SceneMain_h */
