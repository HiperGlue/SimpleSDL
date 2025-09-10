#pragma once

#include <vector>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ENGINE/engine.hpp"

class Player : public Object{
    private:
        Vector velocity;
        bool onGround;
    public:
        std::shared_ptr<Transform> transform;
        std::shared_ptr<Sprite> sprite;

        Vector GetVelocity();
        bool GetOnGround();

        void SetVelocity(Vector _velocity);
        void SetOnGround(bool _onGround);

        /*------------------------------GAME PROCESSES------------------------------*/

        Player();
        void Update(float deltaTime) override;
};
