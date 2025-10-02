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

        Vector targetResolution;
    public:
        /*------------------------------GAME PROCESSES------------------------------*/
        
        Camera(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;
        void Render();

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        const std::shared_ptr<Transform>& GetTransform();

        void SetBackgroundColor(Color _backgroundColor);
        void SetTargetRenderer(SDL_Renderer* _targetRenderer);
        void SetTargetResolution(float resolutionWidth, float resolutionHeight);
        void SetTargetResolution(Vector _targetResolution);
};
