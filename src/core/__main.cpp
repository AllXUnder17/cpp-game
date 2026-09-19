// #include "raylib.h"
// #include <vector>
// #include <string>

// int main() {
//     const int screenWidth = 800;
//     const int screenHeight = 600;

//     InitWindow(screenWidth, screenHeight, "Raylib - Procedural ASCII Pixel Art Cutout");
//     SetTargetFPS(60);

//     // 1. Create/Load your Low-Res Pixel Art Mask
//     // Small resolution (e.g., 64x48) keeps performance fast and matches character cell scaling.
//     const int maskWidth = 64;
//     const int maskHeight = 48;

//     // Load your pixel art texture here:
//     Texture2D pixelArt = LoadTexture("assets/gfx/skull.png");
    
//     // For demonstration: Generate a simple pixel art heart mask on GPU
//     RenderTexture2D maskTarget = LoadRenderTexture(maskWidth, maskHeight);
//     BeginTextureMode(maskTarget);
//         ClearBackground(BLANK);

//         DrawTexture(pixelArt, 0, 0, WHITE);
//     EndTextureMode();

//     // 2. Fetch the pixel array from GPU -> CPU memory
//     Image maskImage = LoadImageFromTexture(maskTarget.texture);
//     Color* maskPixels = LoadImageColors(maskImage);

//     // Procedural text source (Matrix/Code aesthetic)
//     const std::string charSet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ#@$%&*=";
    
//     // Grid sizing
//     const int cellWidth = screenWidth / maskWidth;   // 12px wide per char
//     const int cellHeight = screenHeight / maskHeight; // 12px high per char
//     const int fontSize = 12;

//     while (!WindowShouldClose()) {
//         float time = (float)GetTime();

//         BeginDrawing();
//             ClearBackground(BLACK);

//             // 3. Loop through every pixel cell in the low-res pixel art mask
//             for (int y = 0; y < maskHeight; y++) {
//                 for (int x = 0; x < maskWidth; x++) {
                    
//                     // Raylib RenderTexture Y-coordinates are inverted
//                     int pixelIndex = (maskHeight - 1 - y) * maskWidth + x;
//                     Color maskColor = maskPixels[pixelIndex];

//                     // Determine screen position for this ASCII character
//                     int screenX = x * cellWidth;
//                     int screenY = y * cellHeight;

//                     // CUTOUT MASK LOGIC:
//                     // If the pixel art pixel is opaque (part of your artwork), DON'T draw text
//                     if (maskColor.a > 50) {
//                         continue; // Cutout hole!
//                     }

//                     // PROCEDURAL ASCII GENERATION:
//                     // Pick a dynamic character based on position + time
//                     int charIdx = (x * 7 + y * 13 + (int)(time * 15.0f)) % charSet.length();
//                     char glyph[2] = { charSet[charIdx], '\0' };

//                     // Optional: Fade colors procedurally across the grid
//                     unsigned char greenVal = (unsigned char)((x + y + (int)(time * 20)) % 155 + 100);
//                     Color textColor = { 0, greenVal, 50, 255 };

//                     DrawText(glyph, screenX, screenY, fontSize, textColor);
//                 }
//             }

//             DrawFPS(10, 10);
//         EndDrawing();
//     }

//     // Cleanup CPU/GPU resources
//     UnloadImageColors(maskPixels);
//     UnloadImage(maskImage);
//     UnloadRenderTexture(maskTarget);

//     CloseWindow();
//     return 0;
// }