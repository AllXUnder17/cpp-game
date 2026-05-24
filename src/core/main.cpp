#include "libraryofalexandria.h"

int main() {
    GameManager::InitGame(/*width:*/ 1280, /*height:*/ 720);

    
    Player player = Player(
        GameObjectConfig{
            //.sprite = SpriteLoader::GetSprite("man.png"),
            .position = { 0, 0 }
        }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 
            16, 
            {2}
        ), 300);
    
    Weapon w = Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = &player,
        .localPosition = { 10, 5 }
    }, { 12, -1 }, 
    5);
    
    float rndPosX = rand() * 100;
    float rndPosY = rand() * 100;

    bool toggleNerdInfo = true;
    float deltaTime;
    float elapsedCoinSpawnTime = 0.0f;

    while (!WindowShouldClose()) {
        elapsedCoinSpawnTime += GetFrameTime();
        // if (elapsedCoinSpawnTime > 1){
        //     float rndPosX = rand() % 100;
        //     float rndPosY = rand() % 100;

        //     Coin* c = new Coin(GameObjectConfig{
        //         .position = {rndPosX, rndPosY}
        //         },
        //         SpriteSheet(
        //             SpriteLoader::GetSprite("coin_spritesheet.png"),
        //             16, 16, 
        //             {2}
        //         ));

        //     elapsedCoinSpawnTime = 0.0f;
        // }

        //===OTHERS===
        deltaTime = GetFrameTime();
        
        if (IsKeyPressed(KEY_TAB))
            toggleNerdInfo = !toggleNerdInfo;

        //===HANDLE UPDATABLES===
        GameManager::HandleUpdatables();

        //===HANDLE GFX===
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
                // std::stringstream nerdInfoText;

                // nerdInfoText << std::fixed << std::setprecision(6) <<
                //     "T: [DT: " << deltaTime << ",\t FPS:" << 1.0f / deltaTime << "]\n\n" <<
                //     "===MANAGERS===\n\n";

                // GFXManager::OutputInfo(nerdInfoText);

                // nerdInfoText <<
                //     std::fixed << std::setprecision(2) <<
                //     "PL: [X: " << player.GetPosition().x  << ",\t Y: " << player.GetPosition().y << "]\n\n" <<
                //     "----\n\n"
                //     "W: [ROT: " << w.GetRotation() << "]\n\n" << 
                //     "B: [CNT: " << "]";

                // DrawText(nerdInfoText.str().c_str(), 10, 10, 24, BLACK);
            }

        EndDrawing();
    }

    GameManager::UninitGame();

    return 0;
}