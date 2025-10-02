#pragma once

#include <variant>

struct Keyframe{
    int timestamp;
    Uint64 componentID;
    //needs to only be tied to component things
    //something to relate the changed property to its owner
    //the changed property
    //the value or function
};

struct Animation{
    int tickrate;
    std::vector<Keyframe> keyframes;
};

class Animator{
    Animation animation;
};
