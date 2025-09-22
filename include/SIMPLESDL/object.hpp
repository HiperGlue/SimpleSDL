#pragma once

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Entity{
    public:
        int ID;
        int componentCount = 0;
        Entity(int _ID);
};

class Component{
    public:
        int ID;
        int entityID;
        Component(int _ID, int _entityID);

        int GetEntityID();

        virtual void Update() = 0;
};

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

class Transform : public Component{
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

        void Update() override {};

        Transform(int ID, int entityID);
};

class Sprite : public Component{
    private:
        SDL_Texture* texture;
        Color color;

        bool flipX = false;
        bool flipY = false;

        bool mirrorX = false;
        bool mirrorY = false;
    public:
        void SetTexture(const char* imgFile, SDL_ScaleMode scaleMode = SDL_SCALEMODE_NEAREST);
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

        Sprite(int ID, int entityID);

        void Update() override {};
};

/*class Object{
    public:
        virtual void Update(float deltaTime) = 0;
};*/
