#pragma once

#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

struct Vector{
    float x;
    float y;
    float magnitude;

    Vector(float _x = 0.0f, float _y = 0.0f);

    Vector Normalize();

    bool operator == (const Vector &v) const;
    Vector operator + (const Vector &v) const;
    Vector operator - (const Vector &v) const;
    Vector operator * (const float &s) const;
    float operator * (const Vector &v) const;
};

struct Color{
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;

    Color(Uint8 _red = 255, Uint8 _green = 255, Uint8 _blue = 255, Uint8 _alpha = 255);
};

class Transform{
    private:
        Vector position;
        float angle;
        Vector size;
    public:
        void SetPosition(Vector _position);
        void SetAngle(float _angle);
        void SetSize(Vector _size);

        Vector GetPosition();
        float GetAngle();
        Vector GetSize();
};

class Sprite{
    private:
        SDL_Texture* texture;
        Color color;

        bool flipX;
        bool flipY;

        bool mirrorX;
        bool mirrorY;
    public:
        std::shared_ptr<Transform> transform;
        void SetTexture(const char* imgFile);
        void SetColor(SDL_Color _color);
        void SetFlipX(bool _flipX);
        void SetFlipY(bool _flipY);
        void SetMirrorX(bool _flipX);
        void SetMirrorY(bool _flipY);

        SDL_Texture* GetTexture();
        Color GetColor();
        bool GetFlipX();
        bool GetFlipY();
        bool GetMirrorX();
        bool GetMirrorY();

        /*------------------------------GAME PROCESSES------------------------------*/

        Sprite(std::shared_ptr<Transform> _transform);
};

class Object{
    public:
        virtual void Update(float deltaTime) = 0;
};
