#pragma once

#include <memory>

#include "SIMPLESDL/object.hpp"

class Collider : public Component{
    private:
        std::shared_ptr<Transform> transform;

        Vector offset;
        Vector size;
    public:
        /*------------------------------GAME PROCESSES------------------------------*/

        Collider(int ID, int entityID);
        void Start() override;
        void Update() override;

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetOffset(Vector _offset);
        void SetSize(Vector _size);

        const std::shared_ptr<Transform>& GetTransform();

        Vector GetOffset();
        Vector GetSize();

        std::vector<Vector> GetColliderVerticies(Vector position);

        bool CheckCollision(Vector direction);
        Vector CollideAndSlide(Vector direction);
};
