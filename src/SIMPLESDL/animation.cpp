#include "SIMPLESDL/animation.hpp"

Keyframe::Keyframe(int _timestamp, std::shared_ptr<Component> _component){ timestamp = _timestamp; component = _component; }
Keyframe::~Keyframe(){}

Animation::Animation(){ tickrate = 100; }

Animator::Animator(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){
    animation = Animation();
}
