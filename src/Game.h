#ifndef GAME_H
#define GAME_H

#include "Scene.h"

class Game {
    
public:
    Game();
    ~Game();
    void run();
    void quit();
    void update();
    void init();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event* e);
    void render();
    void updateScene();

private:
    bool isRunning = true;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int width = 600;
    int height = 00;

};

#endif // GAME_H
