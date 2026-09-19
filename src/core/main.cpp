#include "libraryofalexandria.h" // IWYU pragma: keep

int main() {

    SceneManager::LoadScene("sc1");

    // try {
    //     sc1.LoadFromFile();

    // } catch (const std::exception& e) {
    //     TraceLog(LOG_ERROR, e.what());
    // }

    GameManager::InitGame(1920, 1080);

    Player* player = GameManager::InstantiateGameObject<Player>(EntityConfig {GameObjectConfig{ .name = "player" }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 16,
            {3}), Vector2 { 16,16 }, CollisionLayer::PLAYER}, 200);

    SerializationManager::LoadGame();
        
    Weapon* w = GameManager::InstantiateGameObject<Weapon>(WeaponConfig {
        GameObjectConfig{
            .name = "weapon",
            .sprite = SpriteLoader::GetSprite("gun.png"),
            .parent = player,
            .localPosition = { 10, 5 }, 
        }, Vector2 { 12, -1 },
        5, 10, 10,  Sound()});
    
    Entity* portal = GameManager::InstantiateGameObject<Entity>(EntityConfig {
        GameObjectConfig {
            .name = "portal",
            .tag = "portal",
            .sprite = SpriteLoader::GetSprite("bullet.png"),
            .position = { 50, 50 }
        }
    });

    // Weapon* sungun = GameManager::InstantiateGameObject<Weapon>(WeaponConfig{
    //     GameObjectConfig{
    //         .sprite = SpriteLoader::GetSprite("sungun_spritesheet.png"),
    //         .parent = player,
    //         .localPosition = { 10, 5 }, 
    //     }, Vector2 { 12, -1 }, 5, 10, 10,  Sound()});

    bool toggleNerdInfo = true;

    CollectableFactory::SpawnCoin({-40, -40});

    EnemyFactory::SpawnBaseEnemy({50, 50});

    InputManager::SetKeybind(KEY_TAB, [&toggleNerdInfo]() { toggleNerdInfo = !toggleNerdInfo; }, ON_KEY_PRESSED);

    //===ASCII STUFF SETUP===
    const int maskWidth = 64;
    const int maskHeight = 48;

    // Load your pixel art texture here:
    Texture2D pixelArt = LoadTexture("assets/gfx/skull.png");
    
    // For demonstration: Generate a simple pixel art heart mask on GPU
    RenderTexture2D maskTarget = LoadRenderTexture(maskWidth, maskHeight);
    BeginTextureMode(maskTarget);
        ClearBackground(BLANK);

        DrawTexture(pixelArt, 0, 0, WHITE);
    EndTextureMode();

    // 2. Fetch the pixel array from GPU -> CPU memory
    Image maskImage = LoadImageFromTexture(maskTarget.texture);
    Color* maskPixels = LoadImageColors(maskImage);

    // Procedural text source (Matrix/Code aesthetic)
    const std::string charSet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ#@$%&*=";
    
    // Grid sizing
    const int cellWidth = 5;   // 12px wide per char
    const int cellHeight = 5; // 12px high per char
    const int fontSize = 3;

    while (!WindowShouldClose()) {
        float time = (float)GetTime();
        

        //===HANDLE UPDATABLES===
        GameManager::HandleUpdate();

        //===HANDLE GFX===
        //Draw screen content to canvas (GFX buffer)
        BeginTextureMode(GFXManager::GetCanvas());
            
            ClearBackground(GFXManager::BACKGROUND_COLOR);

            // for (int y = 0; y < maskHeight; y++) {
            //     for (int x = 0; x < maskWidth; x++) {
                    
            //         // Raylib RenderTexture Y-coordinates are inverted
            //         int pixelIndex = (maskHeight - 1 - y) * maskWidth + x;
            //         Color maskColor = maskPixels[pixelIndex];

            //         // Determine screen position for this ASCII character
            //         int screenX = x * cellWidth;
            //         int screenY = y * cellHeight;

            //         // CUTOUT MASK LOGIC:
            //         // If the pixel art pixel is opaque (part of your artwork), DON'T draw text
            //         if (maskColor.a > 50) {
            //             continue; // Cutout hole!
            //         }

            //         // PROCEDURAL ASCII GENERATION:
            //         // Pick a dynamic character based on position + time
            //         int charIdx = (x * 7 + y * 13 + (int)(time * 15.0f)) % charSet.length();
            //         char glyph[2] = { charSet[charIdx], '\0' };

            //         // Optional: Fade colors procedurally across the grid
            //         unsigned char greenVal = (unsigned char)((x + y + (int)(time * 20)) % 155 + 100);
            //         Color textColor = { 0, greenVal, 50, 255 };

            //         GFXManager::GetCanvas();

                    

            //         DrawText(glyph, screenX, screenY, fontSize, textColor);
            //     }
            // }

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

                nerdInfoText << std::fixed << std::setprecision(6) <<
                    "===SCENES===" << "\n\n" <<
                    "Loaded Scenes: " << SceneManager::GetLoadedScenes().size() << "\n\n" <<
                    "Loaded Game Objects: " << SceneManager::GetLoadedGameObjects().size() << "\n\n";

                nerdInfoText << "----------\n\n";

                nerdInfoText <<
                    std::fixed << std::setprecision(2) <<
                    "PL: [ POS_X: " << player->GetPosition().x  << ",\t POS_Y: " << player->GetPosition().y << "\n\n"
                    << "\tDIR_X: " << player->GetVelocity().x << ",\t DIR_Y: " << player->GetVelocity().y << " ]\n\n" <<
                    "----\n\n";

                DrawText(nerdInfoText.str().c_str(), 10, 10, 24, BLACK);

                //====DISPLAY COLLIDERS===
                Color colliderColor = Color{ 0, 228, 48, 100 };
                Color outlineColor  = Color{ 0, 228, 48, 255 };

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

    // try {
    //     sc1.SaveToFile();
    // } catch (const char* msg) {
    //     TraceLog(LOG_WARNING, msg);
    // }

    SerializationManager::SaveGame();

    GameManager::UninitGame();

    return 0;
}