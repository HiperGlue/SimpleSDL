#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/object.hpp"

class Camera : public Component{
    protected:
        std::shared_ptr<Transform> transform;

        Color backgroundColor;
        SDL_Renderer* targetRenderer;
    public:
        /*------------------------------GAME PROCESSES------------------------------*/
        
        Camera(int ID, int entityID);

        void Start() override;
        void Update() override;
        void Render();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetRenderTarget(SDL_Renderer* _targetRenderer);
        void SetBackgroundColor(Color _backgroundColor);

        const std::shared_ptr<Transform>& GetTransform();
};
