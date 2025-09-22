#pragma once

#include <memory>
#include <vector>
#include <concepts>
#include <map>
#include <unordered_map>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/camera.hpp"
#include "SIMPLESDL/collisions.hpp"
#include "SIMPLESDL/object.hpp"

class SIMPLESDL{
    private:
        static SIMPLESDL* instance;

        bool ISRUNNING;
        Uint32 lastTicks;
        float deltaTime;

        SDL_Window* window;
        SDL_Renderer* renderer;

        std::unique_ptr<Camera> mainCamera;
        
        int entityCount;
        std::map<int, std::unique_ptr<Entity>> entities;
        std::vector<std::shared_ptr<Component>> components;

        //std::vector<std::shared_ptr<Object>> updatables;
        //std::vector<std::shared_ptr<Collider>> collidables;

        std::map<SDL_Keycode, SDL_Keycode> keyPoolDown;
        std::map<SDL_Keycode, SDL_Keycode> keyPoolUp;

        /*------------------------------GAME PROCESSES------------------------------*/
        
        SIMPLESDL(){};
        static SIMPLESDL& Get();

        void S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 renderFlags);
        //void S_Events();
        //void S_Update();
        //void S_Render();
        //void S_Clear();

        bool S_IsRunning();
        float S_GetDeltaTime();
        SDL_Renderer* S_GetRenderer();
        SDL_Window* S_GetWindow();

        bool S_GetKeyDown(SDL_Keycode key);
        bool S_GetKeyHold(SDL_Keycode key);
        bool S_GetKeyUp(SDL_Keycode key);
        
        SDL_Texture* S_LoadTexture(const char* file, SDL_ScaleMode scaleMode);
        
        int S_CreateNewEntity();
        
        /*template <class T> void S_AddComponent(int entityID){ //Susceptible a un montón de errores de tipo (tal vez?) !!! Lidiar con eso
            std::unique_ptr<Entity> entity = std::move(entities[entityID]);

            int componentID = entity->componentCount;
            entity->componentCount++;

            std::shared_ptr<T> component = std::make_shared<T>(componentID, entityID);
            components.push_back(component);

            entities[entityID] = std::move(entity);
        }

        
        template <class T> std::shared_ptr<T> S_GetComponent(int entityID){ //Susceptible a un montón de errores de tipo (tal vez?) !!! Lidiar con eso
            for (int i = 0; i < components.size(); i++){
                if (components[i]->entityID != entityID) continue;
                
                std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(components[i]);
                if (component != nullptr) return component;
            }

            return nullptr;
        }*/
    public:
        /*------------------------------GAME PROCESSES------------------------------*/

        static void Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags = 0, Uint32 renderFlags = 0);
        //void Events();
        //void Update();
        //void Render();
        //void Clear();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        static bool IsRunning();
        static float GetDeltaTime();
        static SDL_Renderer* GetRenderer();
        static SDL_Window* GetWindow();

        static bool GetKeyDown(SDL_Keycode key);
        static bool GetKeyHold(SDL_Keycode key);
        static bool GetKeyUp(SDL_Keycode key);
        
        static SDL_Texture* LoadTexture(const char* file, SDL_ScaleMode scaleMode);
        
        static int CreateNewEntity();
        template <class T> static void AddComponent(int entityID){
            std::unique_ptr<Entity> entity = std::move(Get().entities[entityID]);

            int componentID = entity->componentCount;
            entity->componentCount++;

            std::shared_ptr<T> component = std::make_shared<T>(componentID, entityID);
            Get().components.push_back(component);

            Get().entities[entityID] = std::move(entity);
        }
        template <class T> static std::shared_ptr<T> GetComponent(int entityID){
            for (int i = 0; i < Get().components.size(); i++){
                if (Get().components[i]->entityID != entityID) continue;
                
                T* componentCast = dynamic_cast<T*>(Get().components[i].get());
                if (componentCast != nullptr) return std::static_pointer_cast<T>(Get().components[i]);
            }

            return nullptr;
        }

        /*void AddToUpdatables(std::shared_ptr<Object> updatable);
        void AddToCollidables(std::shared_ptr<Collider> collidable);
        void AddToRenderizables(std::shared_ptr<Sprite> renderizable);

        const std::vector<std::shared_ptr<Collider>>& GetCollidables();

        void ClearObjects();*/
};