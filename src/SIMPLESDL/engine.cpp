#include "SIMPLESDL/engine.hpp"

Game* Game::instance = nullptr;

/*------------------------------GAME PROCESSES------------------------------*/

Game& Game::Get(){
    if (instance == nullptr) {
        std::cerr << "Error! Uso de una instancia no definida" << std::endl;
        std::terminate();
    }

    return *instance;
}

void Game::S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 renderFlags){
    std::cout << "Setting everything up..." << std::endl;

    ISRUNNING = true;
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, posX, posY, width, height, windowFlags);
    if (!window){
        std::cerr << "Error while creating main window!!";
        std::terminate();
    }

    if (iconFile[0] != '\0') SDL_SetWindowIcon(window, IMG_Load(iconFile));

    renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if (!renderer){
        std::cerr << "Error while creating renderer!!";
        std::terminate();
    }

    mainCamera = std::make_unique<Camera>(renderer);
    mainCamera->transform->SetSize(Vector(width, height));
}

void Game::S_Events(){
    keyPoolDown.clear();
    keyPoolUp.clear();

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                ISRUNNING = false;
                break;

            case SDL_KEYDOWN:
                keyPoolDown.push_back(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                keyPoolUp.push_back(event.key.keysym.sym);
                break;
            
            default:
                break;
        }
    }
}

void Game::S_Update(){
    Uint32 currentTicks = SDL_GetTicks();
    deltaTime = (currentTicks - Get().lastTicks) / 1000.0f;
    lastTicks = currentTicks;

    for (int i = 0; i < updatables.size(); i++){
        updatables[i]->Update(deltaTime);
    }
}

void Game::S_Render(){
    SDL_RenderClear(renderer);

    mainCamera->Render();

    SDL_RenderPresent(renderer);
}

void Game::S_Clear(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete instance;
    instance = nullptr;
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

bool Game::S_GetKeyDown(SDL_Keycode key){
    for (int i = 0; i < keyPoolDown.size(); i++){
        if (keyPoolDown[i] == key) return true;
    }

    return false;
}

bool Game::S_GetKeyHold(SDL_Keycode key){
    SDL_Scancode scanCode = SDL_GetScancodeFromKey(key);
    return SDL_GetKeyboardState(NULL)[scanCode];
}

bool Game::S_GetKeyUp(SDL_Keycode key){
    for (int i = 0; i < keyPoolUp.size(); i++){
        if (keyPoolUp[i] == key) return true;
    }

    return false;
}

SDL_Texture* Game::S_LoadTexture(const char* file){
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void Game::S_AddToUpdatables(std::shared_ptr<Object> updatable){
    updatables.push_back(updatable);
}

void Game::S_AddToCollidables(std::shared_ptr<Collider> collidable){
    collidables.push_back(collidable);
}

void Game::S_AddToRenderizables(std::shared_ptr<Sprite> renderizable){
    mainCamera->AddToRenderizables(renderizable);
}

void Game::S_ClearObjects(){
    updatables.clear();
    mainCamera->ClearRenderizables();
}



bool Game::IsRunning(){ return Get().ISRUNNING; }
float Game::GetDeltaTime(){ return Get().deltaTime; }
SDL_Renderer* Game::GetRenderer(){ return Get().renderer; }
SDL_Window* Game::GetWindow(){ return Get().window; }

void Game::Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 renderFlags){
    if (!instance){
        instance = new Game();
        std::cout << "Initialization of game done correctly!" << std::endl;
    }
     
    Get().S_Init(title, iconFile, posX, posY, width, height, windowFlags, renderFlags); 
}
void Game::Events(){ Get().S_Events(); }
void Game::Update(){ Get().S_Update(); }
void Game::Render(){ Get().S_Render(); }
void Game::Clear(){ Get().S_Clear(); }
bool Game::GetKeyDown(SDL_Keycode key){ return Get().S_GetKeyDown(key); }
bool Game::GetKeyHold(SDL_Keycode key){ return Get().S_GetKeyHold(key); }
bool Game::GetKeyUp(SDL_Keycode key){ return Get().S_GetKeyUp(key); }
SDL_Texture* Game::LoadTexture(const char* file){ return Get().S_LoadTexture(file); }
void Game::AddToUpdatables(std::shared_ptr<Object> updatable) { Get().S_AddToUpdatables(updatable); }
void Game::AddToCollidables(std::shared_ptr<Collider> collidable) { Get().S_AddToCollidables(collidable); }
void Game::AddToRenderizables(std::shared_ptr<Sprite> renderizable) { Get().S_AddToRenderizables(renderizable); }
const std::vector<std::shared_ptr<Collider>>& Game::GetCollidables() { Get().collidables; }
void Game::ClearObjects(){ Get().ClearObjects(); }
