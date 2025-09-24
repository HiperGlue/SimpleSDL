#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/collisions.hpp"

void Collider::SetOffset(Vector _offset){ offset = _offset; }
void Collider::SetSize(Vector _size){ size = _size; }

Vector Collider::GetOffset(){ return offset; }
Vector Collider::GetSize(){ return size; }

/*------------------------------GAME PROCESSES------------------------------*/

Collider::Collider(std::shared_ptr<Transform> _transform){
    transform = _transform;
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

/*void Collider::CalculateCollision(){
    auto collidables = SIMPLESDL::GetCollidables();
    for (int i = 0; i < collidables.size(); i++){
        auto collidable = collidables[i];
    }
}*/
