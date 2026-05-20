// #include <string>
// #include "raylib.h"
// #include "raymath.h"

// int main() {
//     // 1. Set up your actual monitor window size (High Res)
//     const int windowWidth = 1280;
//     const int windowHeight = 720;
//     InitWindow(windowWidth, windowHeight, "Gungeon Style Pixel Rotation");

//     // 2. Set up your retro virtual resolution (Low Res)
//     const int virtualWidth = 320;
//     const int virtualHeight = 180;

//     // Create the low-res canvas we will build our frame on
//     RenderTexture2D canvas = LoadRenderTexture(virtualWidth, virtualHeight);
//     SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

//     // 3. Load the gun texture from your folder
//     // Place an image named "gun.png" in your project directory
//     Texture2D gunTex = LoadTexture("assets/gfx/gun.png");
//     SetTextureFilter(gunTex, TEXTURE_FILTER_POINT);

//     // 4. Place the gun in the center of our virtual world
//     Vector2 gunPos = { 0.0f, 0.0f };

//     // Setup the Camera to track it
//     Camera2D cam = { 0 };
//     cam.target = gunPos;                                          // Targets (0,0)
//     cam.offset = { virtualWidth / 2.0f, virtualHeight / 2.0f };   // Still centers the lens on the screen
//     cam.rotation = 0.0f;
//     cam.zoom = 1.0f;

//     float rotation = 0.0f;
//     SetTargetFPS(60);

//     while (!WindowShouldClose()) {
//         // ====================================================================
//         // CALCULATIONS & MOUSE TRACKING
//         // ====================================================================

//         if (IsKeyDown(KEY_W))
//             gunPos.y -= 1;
//         if (IsKeyDown(KEY_S))
//             gunPos.y += 1;
//         if (IsKeyDown(KEY_D))
//             gunPos.x += 1;
//         if (IsKeyDown(KEY_A))
//             gunPos.x -= 1;

//         Vector2 mousePos = GetMousePosition();
        
//         // Scale the mouse position down from screen space (1280x720) to virtual canvas space (320x180)
//         Vector2 virtualMousePos = {
//             mousePos.x / (windowWidth / (float)virtualWidth),
//             mousePos.y / (windowHeight / (float)virtualHeight)
//         };

//         // Convert the virtual mouse coordinates into real World Space coordinates via our Camera
//         Vector2 worldMousePos = GetScreenToWorld2D(virtualMousePos, cam);

//         // Calculate the angle between the gun pivot and the world mouse position
//         rotation = atan2f(worldMousePos.y - gunPos.y, worldMousePos.x - gunPos.x) * RAD2DEG;

//         cam.target = Vector2Lerp(gunPos, worldMousePos, 0.3);

//         // ====================================================================
//         // STEP 1: Draw your game onto the tiny, low-res pixel canvas
//         // ====================================================================
//         BeginTextureMode(canvas);
//             ClearBackground(RAYWHITE);

//             // Turn on the camera for our world objects
//             BeginMode2D(cam);
                
//                 // Draw a basic world environment line to see camera stability
//                 DrawLine(-500, virtualHeight / 2, 500, virtualHeight / 2, LIGHTGRAY);

//                 // Setup the rendering bounds for the gun texture
//                 Rectangle source = { 0.0f, 0.0f, (float)gunTex.width, (float)gunTex.height };
//                 Rectangle dest = { gunPos.x, gunPos.y, (float)gunTex.width, (float)gunTex.height };
                
//                 // Set the handle rotation point (adjust these offsets based on your custom sprite)
//                 Vector2 origin = { 2.0f, 4.0f }; 

//                 // Draw the gun inside the camera-tracked world space
//                 DrawTexturePro(gunTex, source, dest, origin, rotation, WHITE);

//             EndMode2D();

//             // --- UI SPACE (Bypasses camera tracking, stays locked to screen) ---
//             std::string debugText = "X: " + std::to_string((int)gunPos.x) + 
//                                     " Y: " + std::to_string((int)gunPos.y) + 
//                                     " Rot: " + std::to_string((int)rotation);
//             DrawText(debugText.c_str(), 8, 8, 10, BLACK);

//         EndTextureMode();

//         // ====================================================================
//         // STEP 2: Blow up the tiny canvas to fit your actual high-res screen
//         // ====================================================================
//         BeginDrawing();
//             ClearBackground(BLACK); 

//             // Flip the Y axis natively because OpenGL render textures are rendered upside down
//             Rectangle canvasSource = { 0.0f, 0.0f, (float)canvas.texture.width, -(float)canvas.texture.height };
//             Rectangle canvasDest = { 0.0f, 0.0f, (float)windowWidth, (float)windowHeight };
//             Vector2 canvasOrigin = { 0.0f, 0.0f };

//             // Draw the upscaled canvas directly onto your physical monitor screen (No camera here!)
//             DrawTexturePro(canvas.texture, canvasSource, canvasDest, canvasOrigin, 0.0f, WHITE);
//         EndDrawing();
//     }

//     // Clean up VRAM allocations
//     UnloadTexture(gunTex);
//     UnloadRenderTexture(canvas);
//     CloseWindow();
//     return 0;
// }