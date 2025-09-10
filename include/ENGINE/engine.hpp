#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "camera.hpp"
#include "collisions.hpp"
#include "object.hpp"

class Game{
    private:
        static Game* instance;

        bool ISRUNNING;
        Uint32 lastTicks;
        float deltaTime;

        SDL_Window* window;
        SDL_Renderer* renderer;

        std::unique_ptr<Camera> mainCamera;

        std::vector<std::shared_ptr<Object>> updatableObjects;

        std::vector<SDL_Keycode> keyPoolDown;
        std::vector<SDL_Keycode> keyPoolUp;
        
        /*------------------------------GAME PROCESSES------------------------------*/
        
        Game(){}
        static Game& Get();

        void S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 renderFlags);
        void S_Events();
        void S_Update();
        void S_Render();
        void S_Clear();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        bool S_GetKeyDown(SDL_Keycode key);
        bool S_GetKeyHold(SDL_Keycode key);
        bool S_GetKeyUp(SDL_Keycode key);
        
        SDL_Texture* S_LoadTexture(const char* file);
        
        void S_AddToUpdatables(std::shared_ptr<Object> updatableObject);
        void S_AddToRenderizables(std::shared_ptr<Sprite> renderizableObject);
        void S_ClearObjects();
    public:
        static bool IsRunning();
        static float GetDeltaTime();
        static SDL_Renderer* GetRenderer();
        static SDL_Window* GetWindow();
        
        /*------------------------------GAME PROCESSES------------------------------*/

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        
        static void Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags = 0, Uint32 renderFlags = 0);
        static void Events();
        static void Update();
        static void Render();
        static void Clear();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        static bool GetKeyDown(SDL_Keycode key);
        static bool GetKeyHold(SDL_Keycode key);
        static bool GetKeyUp(SDL_Keycode key);

        static SDL_Texture* LoadTexture(const char* file);

        static void AddToUpdatables(std::shared_ptr<Object> updatable);
        static void AddToRenderizables(std::shared_ptr<Sprite> renderizable);
        static void ClearObjects();
};