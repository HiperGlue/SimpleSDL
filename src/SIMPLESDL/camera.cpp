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
        Vector renderFactor = resolutionRelation * objectSprite->unitPixelSize;
        std::shared_ptr<Transform> objectTransform = SIMPLESDL::GetComponent<Transform>(objectSprite->GetEntityID());

        Vector centeredPosition = Vector(
            objectTransform->position.x - objectTransform->size.x * .5f,
            -objectTransform->position.y - objectTransform->size.y * .5f
        );

        Color textureColor = objectSprite->color;
        SDL_Texture* renderTexture = objectSprite->GetTexture();
        SDL_SetTextureColorMod
        (
            renderTexture, 
            textureColor.red, textureColor.green, textureColor.blue
        );

        SDL_FlipMode renderFlip = (SDL_FlipMode)(objectSprite->flipX | (objectSprite->flipY * 2));
        
        Vector renderPosition = Vector(
            centeredPosition.x * renderFactor.x - transform->position.x,
            centeredPosition.y * renderFactor.y + transform->position.y
        );
        float renderAngle = objectTransform->angle + transform->angle;
        
        SDL_FRect renderRect = { 
            renderPosition.x + windowResolution.x * .5f,
            renderPosition.y + windowResolution.y * .5f,
            objectTransform->size.x * renderFactor.x,
            objectTransform->size.y * renderFactor.y
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
