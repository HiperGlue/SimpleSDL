#pragma once

#include <memory>
#include <vector>
#include <variant>

#include "SIMPLESDL/object.hpp"

struct Keyframe{
    int timestamp;
    std::shared_ptr<Component> component;

    Keyframe();
};

template<typename T> struct TKeyframe : Keyframe{
    T value;
};

struct Animation{
    int tickrate;
    std::vector<Keyframe> keyframes;

    Animation();
    ~Animation();
};

class Animator : public Component{
    public:
        Animation animation;

        Animator(Uint32 _entityID, Uint32 counter);

        void Start() override;
        void Update() override;
};
