#include "GAME/player.hpp"

Vector Player::GetVelocity(){ return velocity; }
bool Player::GetOnGround(){ return onGround; }

void Player::SetVelocity(Vector _velocity){ velocity = _velocity; }
void Player::SetOnGround(bool _onGround){ onGround = _onGround; }

/*------------------------------GAME PROCESSES------------------------------*/

Player::Player(){
    transform = std::make_shared<Transform>();
    sprite = std::make_shared<Sprite>(transform);

    sprite->SetTexture("assets/images/kirby.png");
    transform->SetSize(Vector(70.0f, 70.0f));
}

void Player::Update(float deltaTime){
    if (Game::GetKeyHold(SDLK_d)){
        Vector position = transform->GetPosition();
        position.x += 100 * deltaTime;
        transform->SetPosition(position);
    }
    transform->SetPosition(transform->GetPosition() + velocity * deltaTime);
}
