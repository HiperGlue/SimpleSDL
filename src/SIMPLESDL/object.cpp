#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/object.hpp"

Vector::Vector(float _x, float _y){
    x = _x;
    y = _y;
    magnitude = SDL_sqrtf(x * x + y * y);
}

Vector Vector::Normalize(){ return Vector(x / magnitude, y / magnitude); }

bool Vector::operator == (const Vector &v) const{ return (x == v.x && y == v.y); }
Vector Vector::operator + (const Vector &v) const{ return Vector(x + v.x, y + v.y); }
Vector Vector::operator - (const Vector &v) const{ return Vector(x - v.x, y - v.y); }
Vector Vector::operator * (const float &s) const{ return Vector(x * s, y * s); }
float Vector::operator * (const Vector &v) const{ return x * v.x + y * v.y; }



Color::Color(Uint8 _red, Uint8 _green, Uint8 _blue , Uint8 _alpha){
    red = _red;
    green = _green;
    blue = _blue;
    alpha = _alpha;
}



void Transform::SetPosition(Vector _position){ position = _position; }
void Transform::SetAngle(float _angle){ angle = _angle; }
void Transform::SetSize(Vector _size){ size = _size; }

Vector Transform::GetPosition(){ return position; }
float Transform::GetAngle(){ return angle; }
Vector Transform::GetSize(){ return size; }



Sprite::Sprite(std::shared_ptr<Transform> _transform){ transform = _transform; }

void Sprite::SetTexture(const char* file, SDL_ScaleMode scaleMode){ texture = SIMPLESDL::LoadTexture(file, scaleMode); }
void Sprite::SetFlipX(bool _flipX) { flipX = _flipX; }
void Sprite::SetFlipY(bool _flipY) { flipY = _flipY; }
void Sprite::SetMirrorX(bool _mirrorX) { mirrorX = _mirrorX; }
void Sprite::SetMirrorY(bool _mirrorY) { mirrorY = _mirrorY; }

SDL_Texture* Sprite::GetTexture(){ return texture; }
Color Sprite::GetColor(){ return color; }
bool Sprite::GetFlipX() { return flipX; }
bool Sprite::GetFlipY() { return flipY; }
bool Sprite::GetMirrorX() { return mirrorX; }
bool Sprite::GetMirrorY() { return mirrorY; }
