#pragma once

#include <memory>
#include <vector>

#include "SIMPLESDL/object.hpp"

class Collider : public Component{
    protected:
        std::shared_ptr<Transform> transform;
    public:
        Vector offset;
        Vector size;

        /*------------------------------GAME PROCESSES------------------------------*/

        Collider(Uint32 _entityID, Uint32 counter);
        void Start() override;
        void Update() override;

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        const std::shared_ptr<Transform>& GetTransform();

        std::vector<Vector> GetColliderVerticies(Vector position);

        bool CheckCollision(Vector direction);
        Vector CollideAndSlide(Vector direction);
};
