#pragma once

#include <vector>

#include "engine.hpp"
#include "object.hpp"

class Collider{
    private:
        std::shared_ptr<Transform> transform;
        Vector offset;
        Vector size;
    public:
        void SetOffset(Vector _offset);
        void SetSize(Vector _size);

        Vector GetOffset();
        Vector GetSize();

        /*------------------------------GAME PROCESSES------------------------------*/

        Collider(std::shared_ptr<Transform> _transform);
        void Update(float deltaTime);

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void CalculateCollision();
};
