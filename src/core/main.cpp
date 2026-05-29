#include "libraryofalexandria.h" // IWYU pragma: keep

int main(int argc, char* argv[]) {
    GameManager::InitGame(1280,720);

    //potencialno tova shte se razkara i shte se zamesti s FactoriesManager iili neshto
    BulletFactory::Init();

    Player* player = GameManager::InstantiateGameObject<Player>(EntityConfig {GameObjectConfig{ }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 16, 
            {2}), Vector2 {16,16}}, 200);

    SerializationManager::LoadGame();
        
    //Sound s = AudioLoader::GetSound("a.mp3", SPAMMABLE);
    // Sound s = LoadSound("../assets/audio/a.mp3");
    // LoadSoundAlias(s);

    Weapon* w = GameManager::InstantiateGameObject<Weapon>(WeaponConfig{
        GameObjectConfig{
            .sprite = SpriteLoader::GetSprite("gun.png"),
            .parent = player,
            .localPosition = { 10, 5 }, 
        }, Vector2 { 12, -1 },
        5, 10,  Sound()});

    bool toggleNerdInfo = true;
    float elapsedCoinSpawnTime = 0.0f;

    Coin* c = GameManager::InstantiateGameObject<Coin>(EntityConfig{
        GameObjectConfig{
            .position = {40, -40}
        },
        SpriteSheet(
            SpriteLoader::GetSprite("coin_spritesheet.png"),
            16, 16, {2} 
        ), Vector2{8., 8}});

    Enemy* e = GameManager::InstantiateGameObject<Enemy>(EntityConfig{
        GameObjectConfig{
            //.sprite = SpriteLoader::GetSprite()
            .position = {50, 50}
        },
        SpriteSheet(
            SpriteLoader::GetSprite("enemy_spritesheet.png"),
            80, 80, {9}
        ),
        Vector2 {40, 40}
    }, 0, 60);

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
                    "T: [DT: " << deltaTime << ",\t FPS:" << 1.0f / deltaTime << "]\n\n" <<
                    "===MANAGERS===\n\n";

                GameManager::OutputInfo(nerdInfoText);
                GFXManager::OutputInfo(nerdInfoText);

                nerdInfoText <<
                    std::fixed << std::setprecision(2) <<
                    "PL: [POS_X: " << player->GetPosition().x  << ",\t POS_Y: " << player->GetPosition().y << "\n\n"
                    << "\tDIR_X: " << player->GetVelocity().x << ",\t DIR_Y: " << player->GetVelocity().y << "]\n\n" <<
                    "----\n\n"
                    "W: [ROT: " << w->GetRotation() << "]\n\n";

                DrawText(nerdInfoText.str().c_str(), 10, 10, 24, BLACK);

                //====DISPLAY COLLIDERS===
                Color colliderColor = Color{ 0, 228, 48, 100 }; // Transparent Green (Lime)
                Color outlineColor  = Color{ 0, 228, 48, 255 }; // Solid Green Outline
            
                for (ICollidable* collidable : CollisionManager::GetActiveCollidables()) {
                    if (collidable == nullptr) continue;
            
                    // Grab the bounding box via the interface contract
                    BoundingBox box = collidable->GetHitbox();
            
                    //TraceLog(LOG_INFO, std::to_string(box.min.x).c_str());
            
                    DrawBoundingBox(box, outlineColor);
            
                }
                //TraceLog(LOG_INFO, "-------");
            }
        EndDrawing();
        
    }

    BulletFactory::Uninit();

    SerializationManager::SaveGame();

    GameManager::UninitGame();

    return 0;
}