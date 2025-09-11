#include "ENGINE/camera.hpp"

/*------------------------------GAME PROCESSES------------------------------*/

Camera::Camera(SDL_Renderer* _targetRenderer){
    transform = std::make_shared<Transform>();
    targetRenderer = _targetRenderer;

    SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 255);
}

void Camera::Render(){
    Vector renderSizeHalf = transform->GetSize() * .5f;

    for (int i = 0; i < renderizables.size(); i++){
        std::shared_ptr<Sprite> objectSprite = renderizables[i];
        std::shared_ptr<Transform> objectTransform = objectSprite->transform;

        Vector centeredPosition = Vector(
            objectTransform->GetPosition().x - objectTransform->GetSize().x * .5f,
            objectTransform->GetPosition().y - objectTransform->GetSize().y * .5f
        );

        Color textureColor = objectSprite->GetColor();
        SDL_Texture* renderTexture = objectSprite->GetTexture();
        SDL_SetTextureColorMod
        (
            renderTexture, 
            textureColor.red, textureColor.green, textureColor.blue
        );

        SDL_RendererFlip renderFlip = (SDL_RendererFlip)(objectSprite->GetFlipX() | (objectSprite->GetFlipY() * 2));
        
        Vector renderPosition = Vector(
            centeredPosition.x + renderSizeHalf.x - transform->GetPosition().x,
            centeredPosition.y + renderSizeHalf.y + transform->GetPosition().y
        );
        float renderAngle = objectTransform->GetAngle() + transform->GetAngle();

        SDL_FRect renderRect = { renderPosition.x, renderPosition.y, objectTransform->GetSize().x, objectTransform->GetSize().y };
        SDL_RenderCopyExF(targetRenderer, renderTexture, NULL, &renderRect, renderAngle, NULL, renderFlip);
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

void Camera::AddToRenderizables(std::shared_ptr<Sprite> renderizable){
    renderizables.push_back(renderizable);
}

void Camera::ClearRenderizables(){ renderizables.clear(); }
