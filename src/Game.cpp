#include "Game.h"
#include "SceneMain.h"
#include <SDL.h>
#include <SDL_image.h>

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::init()
{
    frameTime = 1000 / FPS;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init Error: %s", SDL_GetError());
        isRunning = false;
    }

    //build the window
    window = SDL_CreateWindow("AirPlane war", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    if(window == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow could not be created. %s", SDL_GetError());
        isRunning = false;
    }

    //build the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer could not be created. %s", SDL_GetError());
        isRunning = false;
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init Error. %s", IMG_GetError());
        isRunning = false;
    }

    currentScene = new SceneMain();
    currentScene -> init();
}

void Game::update(float deltaTime) 
{
    currentScene -> update(deltaTime);
}


void Game::clean()
{
    if(currentScene != nullptr){
        currentScene -> clean();
        delete currentScene;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run()
{
    while(isRunning){
        auto frameStart = SDL_GetTicks();

        SDL_Event e;
        handleEvent(&e);
        update(deltaTime);
        render();

        auto frameEnd = SDL_GetTicks();
        auto diff = frameEnd - frameStart;

        if(diff < frameTime){
            SDL_Delay(frameTime - diff);
            deltaTime = frameTime / 1000.0f;
        }else{
            deltaTime = diff / 1000.0f;
        }
    }
}

void Game::changeScene(Scene* scene)
{
    if(currentScene != nullptr){
        currentScene -> clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene -> init();
}

void Game::handleEvent(SDL_Event* e)
{
    while(SDL_PollEvent(e)){
        if(e->type == SDL_QUIT){
            isRunning = false;
        }
        currentScene -> handleEvent(e);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    currentScene -> render();

    SDL_RenderPresent(renderer);
}

