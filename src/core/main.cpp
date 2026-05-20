#include <string>
#include "raylib.h"
#include "raymath.h"

#include "core/gamemanager.h"
#include "core/spriteloader.h"

#include "entities/player.h"
#include "entities/character.h"
#include "entities/weapons/weapon.h"

int main() {
    GameManager::InitGame(/*width:*/ 1280, /*height:*/ 720);

    Player player = Player(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("a.png"),
        .position = { 0, 0 }
    }, 500);

    Weapon w = Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = &player,
        .localPosition = { 200, 400 }
    });

    std::cout << "hello world" << std::endl;

    while (!WindowShouldClose()) {
        GameManager::GetInstance().HandleUpdatables();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            GameManager::GetInstance().HandleDrawables();

            DrawText(
                (std::to_string(player.GetPosition().x) + " " +
                std::to_string(player.GetPosition().y) + " " +
                std::to_string(w.GetPosition().x) + " " +
                std::to_string(w.GetPosition().y)).c_str(),
                0, 0, 16, BLACK
            );
        EndDrawing();
    }

    GameManager::UninitGame();

    return 0;
}