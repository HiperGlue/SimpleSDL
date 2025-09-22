#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SIMPLESDL/object.hpp"

class Camera{
    private:
        std::vector<std::shared_ptr<Sprite>> renderizables;
    protected:
        Color backgroundColor;
        SDL_Renderer* targetRenderer;
    public:
        std::shared_ptr<Transform> transform;

        void SetRenderTarget(SDL_Renderer* _targetRenderer);

        /*------------------------------GAME PROCESSES------------------------------*/
        
        Camera(SDL_Renderer* _targetRenderer);

        void Render();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetBackgroundColor(Color _backgroundColor);
        void AddToRenderizables(std::shared_ptr<Sprite> renderizable);
        void ClearRenderizables();
};
