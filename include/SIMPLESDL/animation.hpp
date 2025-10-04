#pragma once

#include <memory>
#include <vector>
#include <concepts>

#include "SIMPLESDL/object.hpp"


template<typename T> concept numeric = std::is_arithmetic_v<T>;


struct Keyframe{
    int timestamp;
    std::shared_ptr<Component> component;

    Keyframe(int _timestamp, std::shared_ptr<Component> _component) ;
    virtual ~Keyframe() = 0;
};

template<typename T> struct TKeyframe : Keyframe{
    T value;
};

template<numeric T> struct TKeyframe<T> : Keyframe{
    T value;

    void Interpolate();
};

struct Animation{
    int tickrate;
    std::vector<Keyframe> keyframes;

    Animation();
};

class Animator : public Component{
    public:
        Animation animation;

        Animator(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;
};
