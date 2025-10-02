#pragma once

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Entity{
    public:
        Uint32 ID;
        Uint32 componentCounter;
        Entity(Uint32 _ID);
};

class Component{
    protected:
        Uint64 ID;
        Uint32 entityID;
    public:
        Component(Uint32 _entityID, Uint32 counter);
        virtual ~Component() = 0;

        Uint32 GetEntityID();
        Uint64 GetComponentID();

        virtual void Start();
        virtual void Update();
};

struct Vector{
    private:
        float x;
        float y;
        float magnitude;
    public:
        Vector(float _x = 0, float _y = 0);

        float GetX();
        float GetY();
        float GetMagnitude();

        void SetX(float _x);
        void SetY(float _y);

        static Vector Normalize(const Vector &srcVector);
        static float Dot(const Vector &srcVector, const Vector &destVector);
        static Vector Perpendicular(const Vector &srcVector);
        static Vector Project(const Vector &srcVector, const Vector &destVector);
        static Vector Rotate(const Vector &srcVector, const float angle);

        bool operator == (const Vector &v) const;
        Vector operator + (const Vector &v) const;
        Vector operator - (const Vector &v) const;
        Vector operator * (const float &s) const;
        Vector operator * (const Vector &v) const;
        Vector operator / (const Vector &v) const;
};

struct Color{
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;

    Color(Uint8 _red = 255, Uint8 _green = 255, Uint8 _blue = 255, Uint8 _alpha = 255);
};

class Transform : public Component{
    private:
        Vector position;
        float angle;
        Vector size;
    public:
        /*------------------------------GAME PROCESSES------------------------------*/

        Transform(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetPosition(Vector _position);
        void SetAngle(float _angle);
        void SetSize(Vector _size);

        Vector GetPosition();
        float GetAngle();
        Vector GetSize();
};

class Sprite : public Component{
    private:
        SDL_Texture* texture;
        Color color;

        float unitPixelSize;

        bool flipX;
        bool flipY;

        bool mirrorX;
        bool mirrorY;
    public:
        /*------------------------------GAME PROCESSES------------------------------*/

        Sprite(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;

        /*------------------------------MAIN FUNCTIONS------------------------------*/

        void SetTexture(const char* imgFile, SDL_ScaleMode scaleMode = SDL_SCALEMODE_NEAREST);
        void SetColor(Color _color);
        void SetUnitPixelSize(float _unitPixelSize);
        void SetFlipX(bool _flipX);
        void SetFlipY(bool _flipY);
        void SetMirrorX(bool _flipX);
        void SetMirrorY(bool _flipY);

        SDL_Texture* GetTexture();
        Color GetColor();
        float GetUnitPixelSize();
        bool GetFlipX();
        bool GetFlipY();
        bool GetMirrorX();
        bool GetMirrorY();
};
