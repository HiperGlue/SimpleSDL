#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/object.hpp"

class Camera : public Component{
    protected:
        Color backgroundColor;
        SDL_Renderer* targetRenderer;
    public:
        std::shared_ptr<Transform> transform;

        void SetRenderTarget(SDL_Renderer* _targetRenderer);

        /*------------------------------GAME PROCESSES------------------------------*/
        
        Camera(int ID, int entityID);

        void Start() override;
        void Render();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetBackgroundColor(Color _backgroundColor);
};
