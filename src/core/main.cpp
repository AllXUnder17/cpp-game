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

        BeginDrawing();
            ClearBackground(RAYWHITE);

            GameManager::HandleDrawables();

            DrawText(
                (std::to_string(player.GetPosition().x) + " " +
                std::to_string(player.GetPosition().y) + " " +
                std::to_string(w.GetLocalPosition().x) + " " +
                std::to_string(w.GetLocalPosition().y)).c_str(),
                0, 0, 16, BLACK
            );
        EndDrawing();
    }

    GameManager::UninitGame();

    return 0;
}