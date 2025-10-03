#pragma once

#include <memory>
#include <vector>
#include <concepts>
#include <map>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/camera.hpp"
#include "SIMPLESDL/collisions.hpp"
#include "SIMPLESDL/object.hpp"

class SIMPLESDL{
    private:
        static SIMPLESDL* instance;

        SDL_Window* window;
        SDL_Renderer* renderer;

        bool ISRUNNING;
        Uint32 lastTicks;
        float deltaTime;

        Uint32 entityCounter;

        std::map<Uint32, std::unique_ptr<Entity>> entities;
        std::vector<std::shared_ptr<Component>> components;

        std::map<SDL_Keycode, SDL_Keycode> keyPoolDown;
        std::map<SDL_Keycode, SDL_Keycode> keyPoolUp;

        std::shared_ptr<Camera> mainCamera;

        /*------------------------------GAME PROCESSES------------------------------*/
        
        SIMPLESDL(){};
        static SIMPLESDL& Get();

        void S_Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags, Uint32 renderFlags);
        void S_Start();
        void S_Events();
        void S_Update();
        void S_Render();
        void S_Clear();

        bool S_GetKeyDown(SDL_Keycode key);
        bool S_GetKeyHold(SDL_Keycode key);
        bool S_GetKeyUp(SDL_Keycode key);
        
        SDL_Texture* S_LoadTexture(const char* file, SDL_ScaleMode scaleMode);
        
        Uint32 S_CreateNewEntity();

        void S_ClearObjects();
    public:
        /*------------------------------GAME PROCESSES------------------------------*/

        static void Init(const char* title, const char* iconFile, int posX, int posY, int width, int height, Uint32 windowFlags = 0, Uint32 renderFlags = 0);
        static void Start();
        static void Events();
        static void Update();
        static void Render();
        static void Clear();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        static SDL_Renderer* GetRenderer();
        static SDL_Window* GetWindow();
        static Vector GetWindowResolution();
        static float GetWindowAspectRatio();
        static std::shared_ptr<Camera> GetMainCamera();
        static Uint32 GetEntityCounter();
        static bool IsRunning();
        static float DeltaTime();

        static bool GetKeyDown(SDL_Keycode key);
        static bool GetKeyHold(SDL_Keycode key);
        static bool GetKeyUp(SDL_Keycode key);
        
        static SDL_Texture* LoadTexture(const char* file, SDL_ScaleMode scaleMode);
        
        static Uint32 CreateNewEntity();
        template <class T> static std::shared_ptr<T> AddComponent(Uint32 entityID){
            static_assert(
                !std::is_same<Component, T>::value &&
                std::is_base_of<Component, T>::value,
                "Error! Type must be derived from Component"
            );

            std::unique_ptr<Entity> entity = std::move(Get().entities[entityID]);

            std::shared_ptr<T> component = std::make_shared<T>(entityID, entity->componentCounter++);
            Get().components.push_back(component);

            Get().entities[entityID] = std::move(entity);

            return component;
        }
        template <class T> static std::shared_ptr<T> GetComponent(Uint32 entityID){
            static_assert(
                !std::is_same<Component, T>::value &&
                std::is_base_of<Component, T>::value,
                "Error! Type must be derived from Component"
            );

            for (auto component : Get().components){
                if (component->GetEntityID() != entityID) continue;
                
                std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                if (castedComponent) return castedComponent;
            }

            return nullptr;
        }
        template <class T> static std::vector<std::shared_ptr<T>> GetComponents(){
            static_assert(
                !std::is_same<Component, T>::value &&
                std::is_base_of<Component, T>::value,
                "Error! Type must be derived from Component"
            );

            std::vector<std::shared_ptr<T>> castedComponents;

            for (auto component : Get().components){
                std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                if (castedComponent) castedComponents.push_back(castedComponent);
            }

            return castedComponents;
        }
        template <class T> static std::vector<std::shared_ptr<T>> GetComponents(Uint32 entityID){
            static_assert(
                !std::is_same<Component, T>::value &&
                std::is_base_of<Component, T>::value,
                "Error! Type must be derived from Component"
            );

            std::vector<std::shared_ptr<T>> castedComponents;

            for (auto component : Get().components){
                if (component->GetEntityID() != entityID) continue;
                
                std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                if (castedComponent) castedComponents.push_back(castedComponent);
            }

            return castedComponents;
        }
};
