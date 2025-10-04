#pragma once

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct Entity{
    private:
        Uint32 ID;
        Uint32 componentCounter;
    public:
        Entity(Uint32 _ID);
        int GetComponentCounter();
        int Increment();
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
    public:
        float x;
        float y;

        Vector(float _x = 0, float _y = 0);
        
        static float Magnitude(const Vector &srcVector);
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
    public:
        Vector position;
        float angle;
        Vector size;

        /*------------------------------COMPONENT PROCESSES------------------------------*/

        Transform(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;
};

class Sprite : public Component{
    protected:
        SDL_Texture* texture;
    public:
        Color color;

        float unitPixelSize;

        bool flipX;
        bool flipY;

        bool mirrorX;
        bool mirrorY;

        /*------------------------------COMPONENT PROCESSES------------------------------*/

        Sprite(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;

        /*--------------------------------MAIN FUNCTIONS--------------------------------*/

        void SetTexture(const char* imgFile, SDL_ScaleMode scaleMode = SDL_SCALEMODE_NEAREST);
        SDL_Texture* GetTexture();
};
