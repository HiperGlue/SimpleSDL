#include "SIMPLESDL/engine.hpp"

SIMPLESDL* SIMPLESDL::instance = nullptr;

/*------------------------------GAME PROCESSES------------------------------*/

SIMPLESDL& SIMPLESDL::Get(){
    if (instance == nullptr){
        SDL_LogError(1, "Error! Use of undefined instance of SIMPLESDL!!");
        std::terminate();
    }

    return *instance;
}

void SIMPLESDL::S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 initFlags){
    SDL_Log("Setting everything up...");

    ISRUNNING = true;
    lastTicks = 0;
    deltaTime = 0;
    entityCounter = 0;

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

    int mainCameraID = CreateNewEntity();
    AddComponent<Transform>(mainCameraID);
    mainCamera = AddComponent<Camera>(mainCameraID);
    mainCamera->SetTargetRenderer(renderer);
}

void SIMPLESDL::S_Start(){
    for (auto component : components){
        component->Start();
    }
}

void SIMPLESDL::S_Events(){
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

void SIMPLESDL::S_Update(){
    Uint32 currentTicks = SDL_GetTicks();
    deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;

    for (auto component : components){
        component->Update();
    }
}

void SIMPLESDL::S_Render(){
    SDL_RenderClear(renderer);
    
    mainCamera->Render();

    SDL_RenderPresent(renderer);
}

void SIMPLESDL::S_Clear(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

bool SIMPLESDL::S_GetKeyDown(SDL_Keycode key){
    for (int i = 0; i < keyPoolDown.size(); i++){
        if (keyPoolDown[i] == key) return true;
    }

    return false;
}

bool SIMPLESDL::S_GetKeyHold(SDL_Keycode key){
    SDL_Scancode scanCode = SDL_GetScancodeFromKey(key, NULL);
    return SDL_GetKeyboardState(NULL)[scanCode];
}

bool SIMPLESDL::S_GetKeyUp(SDL_Keycode key){
    for (int i = 0; i < keyPoolUp.size(); i++){
        if (keyPoolUp[i] == key) return true;
    }

    return false;
}

SDL_Texture* SIMPLESDL::S_LoadTexture(const char* file, SDL_ScaleMode scaleMode){
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_SetTextureScaleMode(texture, scaleMode);
    SDL_DestroySurface(tmpSurface);

    return texture;
}

Uint32 SIMPLESDL::S_CreateNewEntity(){
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(entityCounter);
    entities[entityCounter] = std::move(entity);

    entityCounter++;
    return entityCounter - 1;
}

/*------------------------------ACCESSERS------------------------------*/

SDL_Renderer* SIMPLESDL::GetRenderer(){ return Get().renderer; }
SDL_Window* SIMPLESDL::GetWindow(){ return Get().window; }
Vector SIMPLESDL::GetWindowResolution(){
    int width, height;
    SDL_GetWindowSize(Get().window, &width, &height);
    return Vector(width, height);
}
float SIMPLESDL::GetWindowAspectRatio(){
    float aspect;
    SDL_GetWindowAspectRatio(Get().window, &aspect, NULL);
    return aspect;
}
std::shared_ptr<Camera> SIMPLESDL::GetMainCamera(){ return Get().mainCamera; }
Uint32 SIMPLESDL::GetEntityCounter(){ return Get().entityCounter; }
bool SIMPLESDL::IsRunning(){ return Get().ISRUNNING; }
float SIMPLESDL::DeltaTime(){ return Get().deltaTime; }

void SIMPLESDL::Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 initFlags){
    if (!instance){
        instance = new SIMPLESDL();
    }

    Get().S_Init(title, iconFile, posX, posY, width, height, windowFlags, initFlags); 
}
void SIMPLESDL::Start(){ Get().S_Start(); }
void SIMPLESDL::Events(){ Get().S_Events(); }
void SIMPLESDL::Update(){ Get().S_Update(); }
void SIMPLESDL::Render(){ Get().S_Render(); }
void SIMPLESDL::Clear(){ Get().S_Clear(); }
bool SIMPLESDL::GetKeyDown(SDL_Keycode key){ return Get().S_GetKeyDown(key); }
bool SIMPLESDL::GetKeyHold(SDL_Keycode key){ return Get().S_GetKeyHold(key); }
bool SIMPLESDL::GetKeyUp(SDL_Keycode key){ return Get().S_GetKeyUp(key); }
SDL_Texture* SIMPLESDL::LoadTexture(const char* file, SDL_ScaleMode scaleMode){ return Get().S_LoadTexture(file, scaleMode); }

Uint32 SIMPLESDL::CreateNewEntity(){ return Get().S_CreateNewEntity(); }
