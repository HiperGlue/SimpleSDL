#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/object.hpp"
#include "SIMPLESDL/utils.hpp"

/*---------------------------------ENTITY CLASS---------------------------------*/

Entity::Entity(Uint32 _ID){ ID = _ID; componentCounter = 0; }
int Entity::GetComponentCounter(){ return componentCounter; }
int Entity::Increment(){ return componentCounter++; }

/*--------------------------------COMPONENT BASE--------------------------------*/

Component::Component(Uint32 _entityID, Uint32 counter){ ID = (_entityID << 16) | counter; entityID = _entityID; }
Component::~Component(){}
Uint32 Component::GetEntityID(){ return entityID; }
Uint64 Component::GetComponentID(){ return ID; }
void Component::Start(){}
void Component::Update(){}

/*---------------------------------VECTOR STRUCT--------------------------------*/

Vector::Vector(float _x, float _y){
    x = _x;
    y = _y;
}

float Vector::Magnitude(const Vector &srcVector){ return SSDL_SQRT(srcVector.x * srcVector.x + srcVector.y * srcVector.y); }

Vector Vector::Normalize(const Vector &srcVector){
    float magnitude = Vector::Magnitude(srcVector);

    if (magnitude == 0) return Vector();
    return Vector(srcVector.x / magnitude, srcVector.y / magnitude); 
}
float Vector::Dot(const Vector &srcVector, const Vector &destVector) { return srcVector.x * destVector.x + srcVector.y * destVector.y; }
Vector Vector::Perpendicular(const Vector &srcVector){ 
    return Vector::Normalize(Vector(-srcVector.y, srcVector.x)); 
}
Vector Vector::Project(const Vector &srcVector, const Vector &destVector){
    float magnitude = Vector::Magnitude(destVector);

    if (magnitude == 0) return Vector();
    return Vector::Normalize(destVector * (Vector::Dot(srcVector, destVector) / (magnitude * magnitude)));
}
Vector Vector::Rotate(const Vector &srcVector, const float angle){
    float radAngle = SSDL_DEG2RADS(angle);
    float cos = SSDL_COS(radAngle);
    float sin = SSDL_SIN(radAngle);
    
    float x = srcVector.x * cos - srcVector.y * sin;
    float y = -(srcVector.x * sin + srcVector.y * cos);

    return Vector(x,y);
}

bool Vector::operator == (const Vector &v) const{ return (x == v.x && y == v.y); }
Vector Vector::operator + (const Vector &v) const{ return Vector(x + v.x, y + v.y); }
Vector Vector::operator - (const Vector &v) const{ return Vector(x - v.x, y - v.y); }
Vector Vector::operator * (const float &s) const{ return Vector(x * s, y * s); }
Vector Vector::operator * (const Vector &v) const{ return Vector(x * v.x, y * v.y); }
Vector Vector::operator / (const Vector &v) const{ return Vector(x / v.x, y / v.y); }

/*---------------------------------COLOR STRUCT---------------------------------*/

Color::Color(Uint8 _red, Uint8 _green, Uint8 _blue , Uint8 _alpha){
    red = _red;
    green = _green;
    blue = _blue;
    alpha = _alpha;
}

/*------------------------------TRANSFORM COMPONENT------------------------------*/

Transform::Transform(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){
    position = Vector();
    angle = 0;
    size = Vector(1,1);
};

void Transform::Start(){}
void Transform::Update(){}

/*--------------------------------SPRITE COMPONENT-------------------------------*/

Sprite::Sprite(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){
    texture = nullptr;
    color = Color();

    unitPixelSize = 100;

    flipX = false;
    flipY = false;

    mirrorX = false;
    mirrorY = false;
};

void Sprite::Start(){}
void Sprite::Update(){}

void Sprite::SetTexture(const char* file, SDL_ScaleMode scaleMode){ texture = SIMPLESDL::LoadTexture(file, scaleMode); }
SDL_Texture* Sprite::GetTexture(){ return texture; }
