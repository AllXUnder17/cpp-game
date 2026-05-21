#include "libraryofalexandria.h"

int main() {
    GameManager::InitGame(/*width:*/ 1280, /*height:*/ 720);

    
    Player player = Player(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("man.png"),
        .position = { 0, 0 }
    }, 300);
    
    Weapon w = Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = &player,
        .localPosition = { 10, 5 }
    });
    
    bool toggleNerdInfo = false;
    float deltaTime;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB))
            toggleNerdInfo = !toggleNerdInfo;

        deltaTime = GetFrameTime();

        GameManager::HandleUpdatables();

        //Draw screen content to canvas (GFX buffer)
        BeginTextureMode(GFXManager::GetCanvas());
            
            ClearBackground(GFXManager::BACKGROUND_COLOR);

            GFXManager::DrawCanvas();
            
        EndTextureMode();
        
        //Render canvas
        BeginDrawing();
            
            ClearBackground(GFXManager::BACKGROUND_COLOR);

            GFXManager::RenderCanvas();

            if (toggleNerdInfo) {
                std::stringstream nerdInfoText;

                nerdInfoText << std::fixed << std::setprecision(6) <<
                    "T: [DT: " << deltaTime << ",\t FPS:" << 1.0f / deltaTime << "]\n\n" <<

                    std::fixed << std::setprecision(2) <<
                    "PL: [X: " << player.GetPosition().x  << ",\t Y: " << player.GetPosition().y << "]\n\n"
                    "W: [ROT: " << w.GetRotation() << "]";

                DrawText(nerdInfoText.str().c_str(), 10, 10, 24, BLACK);
            }

        EndDrawing();
    }

    GameManager::UninitGame();

    return 0;
}