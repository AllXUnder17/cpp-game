#include "libraryofalexandria.h" // IWYU pragma: keep

int main(int argc, char* argv[]) {

    GameManager::InitGame(1280, 720);
    
    Player* player = GameManager::InstantiateGameObject<Player>(EntityConfig {GameObjectConfig{ }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
        16, 16,
            {2}), Vector2 {16,16}, CollisionLayer::PLAYER}, 200);

    SerializationManager::LoadGame();
        
    Weapon* w = GameManager::InstantiateGameObject<Weapon>(WeaponConfig{
        GameObjectConfig{
            .sprite = SpriteLoader::GetSprite("gun.png"),
            .parent = player,
            .localPosition = { 10, 5 }, 
        }, Vector2 { 12, -1 },
        5, 10, 10,  Sound()});

    bool toggleNerdInfo = true;

    CollectableFactory::SpawnCoin({-40, -40});

    EnemyFactory::SpawnBaseEnemy({50, 50});

    InputManager::SetKeybind(KEY_TAB, [&toggleNerdInfo]() { toggleNerdInfo = !toggleNerdInfo;}, ON_KEY_PRESSED);

    while (!WindowShouldClose()) {
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
                float deltaTime = GetFrameTime();

                std::stringstream nerdInfoText;

                nerdInfoText << std::fixed;

                nerdInfoText << std::fixed << std::setprecision(6) <<
                    "T: [ DT: " << deltaTime << ",\t FPS:" << 1.0f / deltaTime << " ]\n\n" <<
                    "===MANAGERS===\n\n";

                GameManager::OutputInfo(nerdInfoText);
                GFXManager::OutputInfo(nerdInfoText);
                PhysicsManager::OutputInfo(nerdInfoText);

                nerdInfoText << "----------\n\n";

                nerdInfoText <<
                    std::fixed << std::setprecision(2) <<
                    "PL: [ POS_X: " << player->GetPosition().x  << ",\t POS_Y: " << player->GetPosition().y << "\n\n"
                    << "\tDIR_X: " << player->GetVelocity().x << ",\t DIR_Y: " << player->GetVelocity().y << " ]\n\n" <<
                    "----\n\n"
                    "W: [ ROT: " << w->GetRotation() << " ]\n\n";

                DrawText(nerdInfoText.str().c_str(), 10, 10, 24, BLACK);

                //====DISPLAY COLLIDERS===
                Color colliderColor = Color{ 0, 228, 48, 100 }; // Transparent Green (Lime)
                Color outlineColor  = Color{ 0, 228, 48, 255 }; // Solid Green Outline

                for (ICollidable* collidable : PhysicsManager::GetActiveCollidables()) {
                    if (collidable == nullptr) continue;

                    // Grab the bounding box via the interface contract
                    BoundingBox box = collidable->GetHitbox();

                    DrawBoundingBox(box, outlineColor);

                }
            }

            std::stringstream playerInfo;

            playerInfo << std::fixed << "Collected coins: " << player->GetCollectedCoins() << "\n\n" <<
                "Enemies killed: " << player->GetEnemiesKilled();
            
            DrawText(playerInfo.str().c_str(), 10, 720 - 64, 32, GRAY);
        EndDrawing();
    }

    SerializationManager::SaveGame();

    GameManager::UninitGame();

    return 0;
}