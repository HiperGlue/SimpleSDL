#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/camera.hpp"
#include "SIMPLESDL/collisions.hpp"
#include "SIMPLESDL/object.hpp"

namespace SIMPLESDL{
    /*------------------------------GAME PROCESSES------------------------------*/

    void Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags = 0, Uint32 renderFlags = 0);
    void Events();
    void Update();
    void Render();
    void Clear();

    /*------------------------------MAIN FUNCTIONS------------------------------*/

    bool IsRunning();
    float GetDeltaTime();
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();

    bool GetKeyDown(SDL_Keycode key);
    bool GetKeyHold(SDL_Keycode key);
    bool GetKeyUp(SDL_Keycode key);
    
    SDL_Texture* LoadTexture(const char* file, SDL_ScaleMode scaleMode);
    
    void AddToUpdatables(std::shared_ptr<Object> updatable);
    void AddToCollidables(std::shared_ptr<Collider> collidable);
    void AddToRenderizables(std::shared_ptr<Sprite> renderizable);

    const std::vector<std::shared_ptr<Collider>>& GetCollidables();

    void ClearObjects();
}