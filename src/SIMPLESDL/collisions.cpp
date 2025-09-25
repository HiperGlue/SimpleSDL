#include <iostream>

#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/collisions.hpp"

void Collider::SetOffset(Vector _offset){ offset = _offset; }
void Collider::SetSize(Vector _size){ size = _size; }

Vector Collider::GetOffset(){ return offset; }
Vector Collider::GetSize(){ return size; }

/*------------------------------GAME PROCESSES------------------------------*/

Collider::Collider(int ID, int entityID) : Component(ID, entityID){
    offset = Vector();
    size = Vector(1,1);
}

void Collider::Start(){
    transform = SIMPLESDL::GetComponent<Transform>(entityID);
}
void Collider::Update(){}

/*------------------------------MAIN FUNCTIONS------------------------------*/

const std::shared_ptr<Transform>& Collider::GetTransform(){ return transform; }

bool Collider::CheckCollisions(Vector newPosition){
    Vector srcPosition = newPosition + offset;
    Vector srcSize = transform->GetSize() * size * 0.5f;

    for (int i = 0; i < SIMPLESDL::GetEntityCounter(); i++){
        if (entityID == i) continue;

        auto colliders = SIMPLESDL::GetComponents<Collider>(i);

        for (auto collider : colliders){
            Vector destPosition = collider->GetTransform()->GetPosition() + collider->GetOffset();
            Vector destSize = collider->GetTransform()->GetSize() * collider->GetSize() * 0.5f;

            if (
                srcPosition.x + srcSize.x <= destPosition.x - destSize.x ||
                srcPosition.x - srcSize.x >= destPosition.x + destSize.x ||
                srcPosition.y + srcSize.y <= destPosition.y - destSize.y ||
                srcPosition.y - srcSize.y >= destPosition.y + destSize.y
            ){ continue; }

            return true;
        }
    }

    return false;
}
