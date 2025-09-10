#include "ENGINE/engine.hpp"
#include "GAME/player.hpp"

int main(int argc, char *argv[]){
    Game::Init
    (
        "SDL2 Engine Test", "assets/images/icon.png", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        800, 600
    );

    std::shared_ptr<Player> player = std::make_shared<Player>();

    Game::AddToUpdatables(player);
    Game::AddToRenderizables(player->sprite);

    while (Game::IsRunning()){
        Game::Events();
        Game::Update();
        Game::Render();
    }

    Game::Clear();
}
