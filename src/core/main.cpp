#include "libraryofalexandria.h" // IWYU pragma: keep

void Hello() {
    TraceLog(LOG_INFO, "Hello world");
}


int main(int argc, char* argv[]) {
    GameManager::InitGame(1280,720);

    //potencialno tova shte se razkara i shte se zamesti s FactoriesManager iili neshto
    BulletFactory::Init();

    Player* player = new Player(
        GameObjectConfig{ }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 
            16, 
            {2}), 
        200);
        
    SerializationManager::LoadGame();
        
    //Sound s = AudioLoader::GetSound("a.mp3", SPAMMABLE);
    // Sound s = LoadSound("../assets/audio/a.mp3");
    // LoadSoundAlias(s);

    Weapon* w = new Weapon(
        GameObjectConfig{
            .sprite = SpriteLoader::GetSprite("gun.png"),
            .parent = player,
            .localPosition = { 10, 5 }}, 
        { 12, -1 }, 
        5, Sound());

    bool toggleNerdInfo = true;
    float elapsedCoinSpawnTime = 0.0f;

    //GFXManager::RemoveDrawable(w);

    // InputManager::GetInstance().SetKeybind(KEY_R, [](){Hello();}, ON_KEY_PRESSED);
    float elapsedBulletWaitTime = 0.0f;

    while (!WindowShouldClose()) {
        //===OTHERS===        
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
            }

        EndDrawing();
    }

    BulletFactory::Uninit();

    SerializationManager::SaveGame();

    GameManager::UninitGame();

    return 0;
}