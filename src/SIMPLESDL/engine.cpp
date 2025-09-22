#include <map>

#include "SIMPLESDL/engine.hpp"

namespace SIMPLESDL{
    /*------------------------------PRIVATE MEMBERS------------------------------*/

    namespace{
        bool ISRUNNING;
        Uint32 lastTicks;
        float deltaTime;

        SDL_Window* window;
        SDL_Renderer* renderer;

        std::unique_ptr<Camera> mainCamera;

        std::vector<std::shared_ptr<Object>> updatables;
        std::vector<std::shared_ptr<Collider>> collidables;

        std::map<SDL_Keycode, SDL_Keycode> keyPoolDown;
        std::map<SDL_Keycode, SDL_Keycode> keyPoolUp;
    }

    /*------------------------------GAME PROCESSES------------------------------*/

    void Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 initFlags){
        SDL_Log("Setting everything up...");

        ISRUNNING = true;
        if (!SDL_Init(initFlags)){
            SDL_LogError(1, "Error! Failed initializing SDL systems!!");
            std::terminate();
        }

        window = SDL_CreateWindow(title, width, height, windowFlags);
        SDL_SetWindowPosition(window, posX, posY);
        if (!window){
            SDL_LogError(1, "Error! Failed creating main window!!");
            std::terminate();
        }

        if (iconFile[0] != '\0') SDL_SetWindowIcon(window, IMG_Load(iconFile));

        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer){
            SDL_LogError(1, "Error! Failed creating main renderer!!");
            std::terminate();
        }

        mainCamera = std::make_unique<Camera>(renderer);
        mainCamera->transform->SetSize(Vector(width, height));
    }

    void Events(){
        keyPoolDown.clear();
        keyPoolUp.clear();

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_EVENT_QUIT:
                    ISRUNNING = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    keyPoolDown[event.key.key] = event.key.key;
                    break;

                case SDL_EVENT_KEY_UP:
                    keyPoolUp[event.key.key] = event.key.key;
                    break;
                
                default:
                    break;
            }
        }
    }

    void Update(){
        Uint32 currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        for (int i = 0; i < updatables.size(); i++){
            updatables[i]->Update(deltaTime);
        }
    }

    void Render(){
        SDL_RenderClear(renderer);

        mainCamera->Render();

        SDL_RenderPresent(renderer);
    }

    void Clear(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    /*------------------------------MAIN FUNCTIONS------------------------------*/

    bool IsRunning(){
        return ISRUNNING;
    }
    float GetDeltaTime(){
        return deltaTime;
    }
    SDL_Renderer* GetRenderer(){
        return renderer;
    }
    SDL_Window* GetWindow(){
        return window;
    }

    bool GetKeyDown(SDL_Keycode key){
        for (int i = 0; i < keyPoolDown.size(); i++){
            if (keyPoolDown[i] == key) return true;
        }

        return false;
    }

    bool GetKeyHold(SDL_Keycode key){
        SDL_Scancode scanCode = SDL_GetScancodeFromKey(key, NULL);
        return SDL_GetKeyboardState(NULL)[scanCode];
    }

    bool GetKeyUp(SDL_Keycode key){
        for (int i = 0; i < keyPoolUp.size(); i++){
            if (keyPoolUp[i] == key) return true;
        }

        return false;
    }

    SDL_Texture* LoadTexture(const char* file, SDL_ScaleMode scaleMode){
        SDL_Surface* tmpSurface = IMG_Load(file);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_SetTextureScaleMode(texture, scaleMode);
        SDL_DestroySurface(tmpSurface);

        return texture;
    }

    void AddToUpdatables(std::shared_ptr<Object> updatable){
        updatables.push_back(updatable);
    }

    void AddToCollidables(std::shared_ptr<Collider> collidable){
        collidables.push_back(collidable);
    }

    void AddToRenderizables(std::shared_ptr<Sprite> renderizable){
        mainCamera->AddToRenderizables(renderizable);
    }

    const std::vector<std::shared_ptr<Collider>>& GetCollidables() { return collidables; }

    void ClearObjects(){
        updatables.clear();
        mainCamera->ClearRenderizables();
    }
}