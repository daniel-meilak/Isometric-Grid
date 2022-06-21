#include<array>
#include<iostream>
#include<vector>

#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"grid.h"
#include"textures.h"
#include"wave.h"

// forward function declarations
void transform(Rectangle& tile);

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   SetTargetFPS(60);

   // initialize grid
   Grid grid(gridWidth,gridHeight);

   // create and add tile, button texture
   Texture2D buttonTexture = LoadTexture("sprites/button.png");
   textureStore.add(buttonTexture);

   // game loop
   while (!WindowShouldClose()){

      // draw scene
      BeginDrawing();
      ClearBackground({144,101,254,0});

      // get current mouse position
      Vector2 mousePos = GetMousePosition();

      // check for and animate mouse hover over tile
      grid.mouseHover(mousePos);

      // wave parameters
      if (button_on){
         if (IsKeyDown(KEY_UP    )){ wave_amplitude++; }
         if (IsKeyDown(KEY_DOWN  )){ wave_amplitude--; }
         if (IsKeyDown(KEY_LEFT  )){ wave_length += 0.00001;}
         if (IsKeyDown(KEY_RIGHT )){ wave_length -= 0.00001;}
         if (IsKeyDown(KEY_SPACE )){ dt += wave_speed; };

         if (IsKeyPressed(KEY_PERIOD)){ wave_speed++;     }
         if (IsKeyPressed(KEY_COMMA )){ wave_speed--;     }      
      }

      DrawText(TextFormat("Wave Amplitude:   %i", wave_amplitude), 0,50,20, BLACK);
      DrawText(TextFormat("Wave length:   %01.04f", wave_length), 0,75,20, BLACK);
      DrawText(TextFormat("Wave Speed:   %i", wave_speed), 0,100,20, BLACK);

      // draw grid to screen
      grid.draw();

      // draw button
      waveButton(grid.tiles, mousePos, buttonTexture);
      
      EndDrawing();
   }

   textureStore.unloadAll();

   CloseWindow();

   return 0;
}