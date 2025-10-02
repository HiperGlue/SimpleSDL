#include "SIMPLESDL/engine.hpp"
#include "SIMPLESDL/camera.hpp"

/*------------------------------GAME PROCESSES------------------------------*/

Camera::Camera(Uint32 _entityID, Uint32 counter) : Component(_entityID, counter){}

void Camera::Start(){
    transform = SIMPLESDL::GetComponent<Transform>(entityID);
    SetBackgroundColor(Color());
}

void Camera::Update(){}

void Camera::Render(){
    Vector windowResolution = SIMPLESDL::GetWindowResolution();
    Vector resolutionRelation = windowResolution / targetResolution;

    std::vector<std::shared_ptr<Sprite>> entitySprites = SIMPLESDL::GetComponents<Sprite>();

    for (auto objectSprite : entitySprites){
        Vector renderFactor = resolutionRelation * objectSprite->GetUnitPixelSize();
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
            centeredPosition.GetX() * renderFactor.GetX() - transform->GetPosition().GetX(),
            centeredPosition.GetY() * renderFactor.GetY() + transform->GetPosition().GetY()
        );
        float renderAngle = objectTransform->GetAngle() + transform->GetAngle();
        
        SDL_FRect renderRect = { 
            renderPosition.GetX() + windowResolution.GetX() * .5f,
            renderPosition.GetY() + windowResolution.GetY() * .5f,
            objectTransform->GetSize().GetX() * renderFactor.GetX(),
            objectTransform->GetSize().GetY() * renderFactor.GetY()
        };
        
        SDL_RenderTextureRotated(targetRenderer, renderTexture, NULL, &renderRect, renderAngle, NULL, renderFlip);
    }
}

/*------------------------------MAIN FUNCTIONS------------------------------*/

const std::shared_ptr<Transform>& Camera::GetTransform(){ return transform; }

void Camera::SetBackgroundColor(Color _backgroundColor){ 
    backgroundColor = _backgroundColor; 
    SDL_SetRenderDrawColor
    (
        targetRenderer, 
        backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha
    ); 
}
void Camera::SetTargetRenderer(SDL_Renderer* _targetRenderer){ targetRenderer = _targetRenderer; }
void Camera::SetTargetResolution(float resolutionWidth, float resolutionHeight){ targetResolution = Vector(resolutionWidth, resolutionHeight); }
void Camera::SetTargetResolution(Vector _targetResolution){ targetResolution = _targetResolution; }
