#include "libraryofalexandria.h"

int main() {
    GameManager::InitGame(/*width:*/ 1280, /*height:*/ 720);

    Player player = Player(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("a.png"),
        .position = { 0, 0 }
    }, 500);

    Weapon w = Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = &player,
        .localPosition = { 100, 200 }
    });

    Weapon w1 = Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = &player,
        .localPosition = { -100, 200 }
    });
    
    while (!WindowShouldClose()) {
        GameManager::HandleUpdatables();

        //MOVE TO GAMEMANAGER::RENDERCANVAS()
        BeginTextureMode(GameManager::GetCanvas());
            ClearBackground(RAYWHITE);

            // Turn on the camera for our world objects
            BeginMode2D(GameManager::GetCamera());

                GameManager::HandleDrawables();

                DrawLine(-500, 0, 500, 0, LIGHTGRAY);

            EndMode2D();

        EndTextureMode();


        //MOVE TO GAMEMANAGER
        BeginDrawing();
            ClearBackground(BLACK); 

            // Flip the Y axis natively because OpenGL render textures are rendered upside down
            Rectangle canvasSource = { 0.0f, 0.0f, (float)GameManager::GetCanvas().texture.width, -(float)GameManager::GetCanvas().texture.height };
            Rectangle canvasDest = { 0.0f, 0.0f, (float)GameManager::WINDOW_WIDTH, (float)GameManager::WINDOW_HEIGHT };
            Vector2 canvasOrigin = { 0.0f, 0.0f };

            // Draw the upscaled canvas directly onto your physical monitor screen (No camera here!)
            DrawTexturePro(GameManager::GetCanvas().texture, canvasSource, canvasDest, canvasOrigin, 0.0f, WHITE);
        EndDrawing();
    }

    GameManager::UninitGame();

    return 0;
}