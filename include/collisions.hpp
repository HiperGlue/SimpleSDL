#pragma once

#include <memory>

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

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void CalculateCollision();
};
