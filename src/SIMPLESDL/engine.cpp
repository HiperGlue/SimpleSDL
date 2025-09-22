#include "SIMPLESDL/engine.hpp"

SIMPLESDL* SIMPLESDL::instance = nullptr;

/*------------------------------GAME PROCESSES------------------------------*/

SIMPLESDL& SIMPLESDL::Get(){
    if (instance == nullptr) {
        SDL_LogError(1, "Error! Use of undefined instance of SIMPLESDL!!");
        std::terminate();
    }

    return *instance;
}

void SIMPLESDL::S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 initFlags){
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

    //mainCamera = std::make_unique<Camera>(renderer);
    //mainCamera->transform->SetSize(Vector(width, height));
}

/*void Events(){
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
}*/

/*------------------------------MAIN FUNCTIONS------------------------------*/

bool SIMPLESDL::S_IsRunning(){ return ISRUNNING; }
float SIMPLESDL::S_GetDeltaTime(){ return deltaTime; }
SDL_Renderer* SIMPLESDL::S_GetRenderer(){ return renderer; }
SDL_Window* SIMPLESDL::S_GetWindow(){ return window; }

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

int SIMPLESDL::S_CreateNewEntity(){
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(entityCount);
    entities[entityCount] = std::move(entity);

    entityCount++;
    return entityCount - 1;
}





bool SIMPLESDL::IsRunning(){ return Get().ISRUNNING; }
float SIMPLESDL::GetDeltaTime(){ return Get().deltaTime; }
SDL_Renderer* SIMPLESDL::GetRenderer(){ return Get().renderer; }
SDL_Window* SIMPLESDL::GetWindow(){ return Get().window; }

void SIMPLESDL::Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 initFlags){
    if (!instance){
        instance = new SIMPLESDL();
    }
     
    Get().S_Init(title, iconFile, posX, posY, width, height, windowFlags, initFlags); 
}
//void Game::Events(){ Get().S_Events(); }
//void Game::Update(){ Get().S_Update(); }
//void Game::Render(){ Get().S_Render(); }
//void Game::Clear(){ Get().S_Clear(); }
bool SIMPLESDL::GetKeyDown(SDL_Keycode key){ return Get().S_GetKeyDown(key); }
bool SIMPLESDL::GetKeyHold(SDL_Keycode key){ return Get().S_GetKeyHold(key); }
bool SIMPLESDL::GetKeyUp(SDL_Keycode key){ return Get().S_GetKeyUp(key); }
SDL_Texture* SIMPLESDL::LoadTexture(const char* file, SDL_ScaleMode scaleMode){ return Get().S_LoadTexture(file, scaleMode); }

int SIMPLESDL::CreateNewEntity(){ return Get().S_CreateNewEntity(); }
//void SIMPLESDL::AddToUpdatables(std::shared_ptr<Object> updatable) { Get().S_AddToUpdatables(updatable); }
//void SIMPLESDL::AddToCollidables(std::shared_ptr<Collider> collidable) { Get().S_AddToCollidables(collidable); }
//void SIMPLESDL::AddToRenderizables(std::shared_ptr<Sprite> renderizable) { Get().S_AddToRenderizables(renderizable); }
//const std::vector<std::shared_ptr<Collider>>& SIMPLESDL::GetCollidables() { return Get().collidables; }
//void SIMPLESDL::ClearObjects(){ Get().ClearObjects(); }


/*void AddToUpdatables(std::shared_ptr<Object> updatable){
    updatables.push_back(updatable);
}

void AddToCollidables(std::shared_ptr<Collider> collidable){
    collidables.push_back(collidable);
}

void AddToRenderizables(std::shared_ptr<Sprite> renderizable){
    mainCamera->AddToRenderizables(renderizable);
}

const std::vector<std::shared_ptr<Collider>>& GetCollidables() { return collidables; }*/

/*void ClearObjects(){
    updatables.clear();
    mainCamera->ClearRenderizables();
}*/