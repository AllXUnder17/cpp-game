#include "libraryofalexandria.h" // IWYU pragma: keep

void Hello() {
    TraceLog(LOG_INFO, "Hello world");
}


int main(int argc, char* argv[]) {
    GameManager::InitGame(1280,720);

    Player* player = new Player(
        GameObjectConfig{
            //.sprite = SpriteLoader::GetSprite("man.png"),
            .position = { 0, 0 }
        }, 
        SpriteSheet(
            SpriteLoader::GetSprite("man_spritesheet.png"),
            16, 
            16, 
            {2}
        ), 200);
    
    //Sound s = AudioLoader::GetSound("a.mp3", SPAMMABLE);
    Sound s = LoadSound("../assets/audio/a.mp3");
    LoadSoundAlias(s);

    Weapon* w = new Weapon(GameObjectConfig{
        .sprite = SpriteLoader::GetSprite("gun.png"),
        .parent = player,
        .localPosition = { 10, 5 }
    }, { 12, -1 }, 
    5, s);

    float rndPosX = rand() * 100;
    float rndPosY = rand() * 100;

    bool toggleNerdInfo = true;
    float deltaTime;
    float elapsedCoinSpawnTime = 0.0f;

    BulletFactory bf = BulletFactory(10);

    // InputManager::GetInstance().SetKeybind(KEY_R, [](){Hello();}, ON_KEY_PRESSED);
    float elapsedBulletWaitTime = 0.0f;

    while (!WindowShouldClose()) {

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            elapsedBulletWaitTime += GetFrameTime();

            if (elapsedBulletWaitTime >= 1.0f / 10) {
                PlaySound(w->GetOnShootSound());
                Vector2 bulletVelocity = Vector2Scale(w->GetOrientation(), 5);

                bf.SpawnBullet(w->GetTipPos(), bulletVelocity);

                elapsedBulletWaitTime = 0;
            }
        }

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

    GameManager::UninitGame();

    return 0;
}