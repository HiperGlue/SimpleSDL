#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/object.hpp"
#include "SIMPLESDL/utils.hpp"

Entity::Entity(Uint32 _ID){ ID = _ID; componentCounter = 0; }



Component::Component(Uint32 _entityID, Uint32 counter){ 
    ID = (_entityID << 16) | counter; entityID = _entityID; 
}
Uint32 Component::GetEntityID(){ return entityID; }
Uint64 Component::GetComponentID(){ return ID; }
void Component::Start(){}
void Component::Update(){}
Component::~Component(){}



Vector::Vector(float _x, float _y){
    x = _x;
    y = _y;
    magnitude = SSDL_SQRT(x * x + y * y);
}

float Vector::GetX(){ return x; }
float Vector::GetY(){ return y; }
float Vector::GetMagnitude(){ return magnitude; }

void Vector::SetX(float _x){ x = _x; magnitude = SSDL_SQRT(x * x + y * y); }
void Vector::SetY(float _y){ y = _y; magnitude = SSDL_SQRT(x * x + y * y); }

Vector Vector::Normalize(const Vector &srcVector){
    if (srcVector.magnitude == 0) return Vector();
    return Vector(srcVector.x / srcVector.magnitude, srcVector.y / srcVector.magnitude); 
}
float Vector::Dot(const Vector &srcVector, const Vector &destVector) { return srcVector.x * destVector.x + srcVector.y * destVector.y; }
Vector Vector::Perpendicular(const Vector &srcVector){ 
    return Vector::Normalize(Vector(-srcVector.y, srcVector.x)); 
}
Vector Vector::Project(const Vector &srcVector, const Vector &destVector){
    if (destVector.magnitude == 0) return Vector();
    return Vector::Normalize(destVector * (Vector::Dot(srcVector, destVector) / (destVector.magnitude * destVector.magnitude)));
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



Color::Color(Uint8 _red, Uint8 _green, Uint8 _blue , Uint8 _alpha){
    red = _red;
    green = _green;
    blue = _blue;
    alpha = _alpha;
}



Transform::Transform(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){
    position = Vector();
    angle = 0;
    size = Vector(1,1);
};

void Transform::Start(){}
void Transform::Update(){}

void Transform::SetPosition(Vector _position){ position = _position; }
void Transform::SetAngle(float _angle){ angle = _angle; }
void Transform::SetSize(Vector _size){ size = _size; }

Vector Transform::GetPosition(){ return position; }
float Transform::GetAngle(){ return angle; }
Vector Transform::GetSize(){ return size; }



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
void Sprite::SetColor(Color _color){ color = _color; }
void Sprite::SetUnitPixelSize(float _unitPixelSize){ unitPixelSize = _unitPixelSize; }
void Sprite::SetFlipX(bool _flipX){ flipX = _flipX; }
void Sprite::SetFlipY(bool _flipY){ flipY = _flipY; }
void Sprite::SetMirrorX(bool _mirrorX){ mirrorX = _mirrorX; }
void Sprite::SetMirrorY(bool _mirrorY){ mirrorY = _mirrorY; }

SDL_Texture* Sprite::GetTexture(){ return texture; }
Color Sprite::GetColor(){ return color; }
float Sprite::GetUnitPixelSize(){ return unitPixelSize; }
bool Sprite::GetFlipX(){ return flipX; }
bool Sprite::GetFlipY(){ return flipY; }
bool Sprite::GetMirrorX(){ return mirrorX; }
bool Sprite::GetMirrorY(){ return mirrorY; }
