#include <iostream>

#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/collisions.hpp"
#include "SIMPLESDL/utils.hpp"

/*------------SAT------------*/



struct Projection{
    float min;
    float max;
};

void GetAxes(std::vector<Vector>& shapeAxes, const std::vector<Vector>& shapeVerticies){
    for (int i = 0; i < shapeVerticies.size(); i++){
        Vector p1 = shapeVerticies[i];
        Vector p2 = shapeVerticies[(i + 1) % shapeVerticies.size()];

        shapeAxes.push_back(Vector::Perpendicular(p1 - p2));
    }
}

Projection GetProjection(const Vector& axis, const std::vector<Vector>& shapeVerticies){
    float min = Vector::Dot(axis, shapeVerticies[0]);
    float max = min;

    for(int i = 1; i < shapeVerticies.size(); i++){
        float projectedPoint = Vector::Dot(axis, shapeVerticies[i]);

        if (projectedPoint < min) min = projectedPoint;
        else if (projectedPoint > max) max = projectedPoint;
    }

    Projection projection = { min, max };
    return projection;
}

bool IsOverlaping(Projection p1, Projection p2){
    if (p1.min <= p2.max && p2.min <= p1.max){
        return true;
    }

    return false;
}

/*------------COLLIDER------------*/

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
void Collider::Update(){
    
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

const std::shared_ptr<Transform>& Collider::GetTransform(){ return transform; }

std::vector<Vector> Collider::GetColliderVerticies(Vector position){
    std::vector<Vector> verticies;

    Vector colliderPosition = position + offset;
    Vector colliderSize = transform->GetSize() * size * 0.5f;

    verticies.push_back(
        Vector::Rotate(Vector(-colliderSize.GetX(), colliderSize.GetY()), transform->GetAngle()) + colliderPosition 
    );
    verticies.push_back(
        Vector::Rotate(Vector(-colliderSize.GetX(), -colliderSize.GetY()), transform->GetAngle()) + colliderPosition 
    );
    verticies.push_back(
        Vector::Rotate(Vector(colliderSize.GetX(), -colliderSize.GetY()), transform->GetAngle()) + colliderPosition 
    );
    verticies.push_back(
        Vector::Rotate(Vector(colliderSize.GetX(), colliderSize.GetY()), transform->GetAngle()) + colliderPosition 
    );

    return verticies;
}

Vector Collider::CollideAndSlide(Vector direction){
    Vector srcOriginalPosition = transform->GetPosition() + offset;
    Vector srcTargetPosition = srcOriginalPosition + direction;
    Vector srcSize = transform->GetSize() * size * 0.5f;

    for (int i = 0; i < SIMPLESDL::GetEntityCounter(); i++){
        if (entityID == i) continue;

        auto posibleCollisions = SIMPLESDL::GetComponents<Collider>(i);

        for (auto collision : posibleCollisions){
            Vector minimumVector;
            float minimumMagnitude = 1000000000000.0f;
            
            std::vector<Vector> selfVerticies = GetColliderVerticies(transform->GetPosition() + direction);
            std::vector<Vector> otherVerticies = collision->GetColliderVerticies(collision->transform->GetPosition());

            std::vector<Vector> selfAxis, otherAxis;
            GetAxes(selfAxis, selfVerticies);
            GetAxes(otherAxis, otherVerticies);

            Projection selfProjection, otherProjection;
            for (Vector axis : selfAxis){
                selfProjection = GetProjection(axis, selfVerticies);
                otherProjection = GetProjection(axis, otherVerticies);

                if (!IsOverlaping(selfProjection, otherProjection)) return srcTargetPosition - offset;

                float overlapMagnitude = SSDL_MIN(selfProjection.max, otherProjection.max) - SSDL_MAX(selfProjection.min, otherProjection.min);
                if (overlapMagnitude < minimumMagnitude){
                    if (selfProjection.min < otherProjection.min) axis = axis * -1;

                    minimumVector = axis;
                    minimumMagnitude = overlapMagnitude;
                }
            }

            for (Vector axis : otherAxis){
                selfProjection = GetProjection(axis, selfVerticies);
                otherProjection = GetProjection(axis, otherVerticies);

                if (!IsOverlaping(selfProjection, otherProjection)) return srcTargetPosition - offset;

                float overlapMagnitude = SSDL_MIN(selfProjection.max, otherProjection.max) - SSDL_MAX(selfProjection.min, otherProjection.min);
                if (overlapMagnitude < minimumMagnitude){
                    if (selfProjection.min < otherProjection.min) axis = axis * -1;

                    minimumVector = axis;
                    minimumMagnitude = overlapMagnitude;
                }
            }

            return srcTargetPosition - offset + minimumVector * minimumMagnitude;
        }
    }

    return srcTargetPosition - offset;
}
