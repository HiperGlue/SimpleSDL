#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/camera.hpp"

/*------------------------------GAME PROCESSES------------------------------*/

Camera::Camera(int ID, int entityID) : Component(ID, entityID){}

void Camera::Start(){
    transform = SIMPLESDL::GetComponent<Transform>(entityID);
    SetBackgroundColor(Color());
}

void Camera::Update(){}

void Camera::Render(){
    Vector renderSizeHalf = transform->GetSize() * .5f;

    for (int i = 0; i < SIMPLESDL::GetEntityCounter(); i++){
        std::vector<std::shared_ptr<Sprite>> entitySprites = SIMPLESDL::GetComponents<Sprite>(i);

        for (auto objectSprite : entitySprites){
            std::shared_ptr<Transform> objectTransform = SIMPLESDL::GetComponent<Transform>(objectSprite->GetEntityID());

            Vector centeredPosition = Vector(
                objectTransform->GetPosition().GetX() - objectTransform->GetSize().GetX() * .5f,
                -objectTransform->GetPosition().GetY() - objectTransform->GetSize().GetY() * .5f
            );

            Color textureColor = objectSprite->GetColor();
            SDL_Texture* renderTexture = objectSprite->GetTexture();
            SDL_SetTextureColorMod
            (
                renderTexture, 
                textureColor.red, textureColor.green, textureColor.blue
            );

            SDL_FlipMode renderFlip = (SDL_FlipMode)(objectSprite->GetFlipX() | (objectSprite->GetFlipY() * 2));
            
            Vector renderPosition = Vector(
                centeredPosition.GetX() + renderSizeHalf.GetX() - transform->GetPosition().GetX(),
                centeredPosition.GetY() + renderSizeHalf.GetY() + transform->GetPosition().GetY()
            );
            float renderAngle = objectTransform->GetAngle() + transform->GetAngle();

            SDL_FRect renderRect = { renderPosition.GetX(), renderPosition.GetY(), objectTransform->GetSize().GetX(), objectTransform->GetSize().GetY() };
            SDL_RenderTextureRotated(targetRenderer, renderTexture, NULL, &renderRect, renderAngle, NULL, renderFlip);
        }
    }
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

void Camera::SetRenderTarget(SDL_Renderer* _targetRenderer){ targetRenderer = _targetRenderer; }

void Camera::SetBackgroundColor(Color _backgroundColor){ 
    backgroundColor = _backgroundColor; 
    SDL_SetRenderDrawColor
    (
        targetRenderer, 
        backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha
    ); 
}

const std::shared_ptr<Transform>& Camera::GetTransform(){ return transform; }
