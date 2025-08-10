#include "SceneMain.h"
#include "Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

SceneMain::SceneMain() : game(Game::getInstance()) {
    
}

SceneMain::~SceneMain() {
    
}

void SceneMain::update(float deltaTime) {
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
}

void SceneMain::render() {

    //render the bullet
    renderPlayerProjectiles();

    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
        static_cast<int>(player.position.y),
        player.width, 
        player.height };
    SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);
}

void SceneMain::init() {
    player.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/SpaceShip.png");
    if(player.texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load player texture: %s", IMG_GetError());
    }
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /=4;
    player.height /=4;
    player.position.x = game.getWindowWidth() / 2 - player.width / 2;
    player.position.y = game.getWindowHeight() - player.height;

    //init bullet template
    projectilePlayerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/laser1.png");
    SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, &projectilePlayerTemplate.width, &projectilePlayerTemplate.height);
    projectilePlayerTemplate.width /= 4;
    projectilePlayerTemplate.height /= 4;
}

void SceneMain::handleEvent(SDL_Event *event) {
    (void)event; // Prevent unused variable warning
}

void SceneMain::clean() {

    //clean the bullet
    for(auto &projectile : playerProjectiles){
        if(projectile != NULL) {
            delete projectile;
        }
    }

    playerProjectiles.clear();
    

    if(player.texture != NULL) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
    if(projectilePlayerTemplate.texture != NULL) {
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
        projectilePlayerTemplate.texture = NULL;
    }
}


void SceneMain::keyboardControl(float deltaTime) {

    auto keyboardState = SDL_GetKeyboardState(NULL);

    if (keyboardState[SDL_SCANCODE_W]){
        player.position.y -= deltaTime * player.speed;  // 基于时间的移动
    }
    if (keyboardState[SDL_SCANCODE_S]){
        player.position.y += deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_A]){
        player.position.x -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_D]){
        player.position.x += deltaTime * player.speed;
    }
    
    // 限制飞机的移动范围
    if (player.position.x < 0){
        player.position.x = 0;
    }
    if (player.position.x > game.getWindowWidth() - player.width){
        player.position.x = game.getWindowWidth() - player.width;
    }
    if (player.position.y < 0){
        player.position.y = 0;
    }
    if (player.position.y > game.getWindowHeight() - player.height){
        player.position.y = game.getWindowHeight() - player.height;
    }

    //shoot func
    if (keyboardState[SDL_SCANCODE_J]){
        auto currentTime = SDL_GetTicks();
        if (currentTime - player.lastShootTime > player.coolDown) { // 限制射击间隔为500毫秒
            shootPlayer();
            player.lastShootTime = currentTime;
        }
    }

}



void SceneMain::shootPlayer() {
    //new bullet
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    //locate in the top center of the player
    projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;
    projectile->position.y = player.position.y;
    playerProjectiles.push_back(projectile);
}


void SceneMain::updatePlayerProjectiles(float deltaTime) {
    int margin = 32; //the max distance that bullet beyond the screen borader
    for (auto it = playerProjectiles.begin(); it != playerProjectiles.end(); ) {
        auto projectile = *it;
        projectile->position.y -= deltaTime * projectile->speed;
        //check whether the bullet is out of the screen
        if (projectile->position.y + margin < 0) {
            delete projectile;
            it = playerProjectiles.erase(it);
        }else{
            ++it;
        }
    }
}


void SceneMain::renderPlayerProjectiles() {
    for (auto projectile : playerProjectiles) {
        SDL_Rect projectileRect = { static_cast<int>(projectile->position.x), 
            static_cast<int>(projectile->position.y),
            projectile->width, 
            projectile->height };
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &projectileRect);
    }
}