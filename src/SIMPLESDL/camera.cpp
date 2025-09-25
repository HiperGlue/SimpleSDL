#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/camera.hpp"

/*------------------------------GAME PROCESSES------------------------------*/

Camera::Camera(int ID, int entityID) : Component(ID, entityID){}

void Camera::Start(){
    transform = SIMPLESDL::GetComponent<Transform>(entityID);
    SetBackgroundColor(Color());
}

void Camera::Render(){
    Vector renderSizeHalf = transform->GetSize() * .5f;

    for (int i = 0; i < SIMPLESDL::GetEntityCount(); i++){
        std::vector<std::shared_ptr<Sprite>> entitySprites = SIMPLESDL::GetComponents<Sprite>(i);

        for (auto objectSprite : entitySprites){
            std::shared_ptr<Transform> objectTransform = SIMPLESDL::GetComponent<Transform>(objectSprite->GetEntityID());

            Vector centeredPosition = Vector(
                objectTransform->GetPosition().x - objectTransform->GetSize().x * .5f,
                -objectTransform->GetPosition().y - objectTransform->GetSize().y * .5f
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
                centeredPosition.x + renderSizeHalf.x - transform->GetPosition().x,
                centeredPosition.y + renderSizeHalf.y + transform->GetPosition().y
            );
            float renderAngle = objectTransform->GetAngle() + transform->GetAngle();

            SDL_FRect renderRect = { renderPosition.x, renderPosition.y, objectTransform->GetSize().x, objectTransform->GetSize().y };
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
