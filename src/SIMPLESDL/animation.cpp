#include "SIMPLESDL/animation.hpp"

Keyframe::Keyframe(){
    timestamp = 0;
    component = nullptr;
}

Animation::Animation(){
    tickrate = 100;
}

Animator::Animator(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){
    animation = Animation();
}
