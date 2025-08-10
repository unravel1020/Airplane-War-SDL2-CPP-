#ifndef GAME_H
#define GAME_H

#include "Scene.h"

class Game {
    
public:

    static Game& getInstance(){
        static Game instance;
        return instance;
    };

    //delete copy constructor and assignment operator
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    void run();
    void quit();
    void update(float deltaTime);
    void init();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event* e);
    void render();
    void updateScene();
    
    SDL_Renderer* getRenderer() { return renderer; }
    int getWindowWidth() { return windowWidth; }
    int getWindowHeight() { return windowHeight; }


private:
    
    Game();
    ~Game();

    bool isRunning = true;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int windowWidth = 600;
    int windowHeight = 800;
    int FPS = 60;
    Uint32 frameTime;
    float deltaTime;


};

#endif // GAME_H
