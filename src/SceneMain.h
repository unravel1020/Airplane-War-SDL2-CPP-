#ifndef SceneMain_h
#define SceneMain_h

#include "Scene.h"
#include "Object.h"
#include "Game.h"
#include <list>

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();
    
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(SDL_Event* event) override;
    void init() override;
    void clean() override;

    void keyboardControl(float deltaTime);

    void shootPlayer();                                 //shoot bullet
    void updatePlayerProjectiles(float deltaTime);      //update bullet
    void renderPlayerProjectiles();                      //render bullet    
    
    
private:

    Game &game;
    Player player;

    ProjectilePlayer projectilePlayerTemplate;

    //save the list of alive bullet
    std::list<ProjectilePlayer*> playerProjectiles;
};

#endif /* SceneMain_h */
