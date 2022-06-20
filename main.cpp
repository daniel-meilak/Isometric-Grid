#include<array>
#include<iostream>
#include<vector>

#include"raylib.h"
#include"raymath.h"

// scale, gridWidth/height, windowSize, transformation matrices
#include"constants.h"
#include"textures.h"
#include"mouse_hover.h"
#include"wave.h"

// forward function declarations
void transform(Rectangle& tile);

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   SetTargetFPS(60);

   // create texture storage
   TextureStorage textureStore;

   // create and add tile, button texture
   Texture2D tileTexture = LoadTexture("sprites/tile.png");
   Texture2D buttonTexture = LoadTexture("sprites/button.png");
   textureStore.add(tileTexture);
   textureStore.add(buttonTexture);

   // tile rectangle for display
   Rectangle tile_source{0.0f, 0.0f, static_cast<float>(tileTexture.width), static_cast<float>(tileTexture.height)};
   std::vector<Rectangle> tiles(gridWidth*gridHeight);

   // set grid positions
   for (int j=0; j<gridHeight; j++){
      for (int i=0; i<gridWidth; i++){
         tiles[i + (j*gridWidth)] = {static_cast<float>(i)*scale,static_cast<float>(j)*scale,scale,scale};
      }
   }

   // transform grid to isometric
   for (auto& tile : tiles){ transform(tile); }

   // game loop
   while (!WindowShouldClose()){

      // draw scene
      BeginDrawing();
      ClearBackground({144,101,254,0});

      // get current mouse position
      Vector2 mousePos = GetMousePosition();

      // check for and animate mouse hover over tile
      mouseHover(tiles,mousePos);

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


      // draw grid
      for (const auto& tile : tiles){
         DrawTexturePro(tileTexture, tile_source, {tile.x, tile.y + waveOffset(tile), tile.width, tile.height}, {}, 0.0f, WHITE);
      }

      // draw button
      waveButton(tiles, mousePos, buttonTexture);
      
      EndDrawing();
   }

   textureStore.unloadAll();

   CloseWindow();

   return 0;
}

void transform(Rectangle& tile){

   Vector3 new_pos = Vector3Transform({tile.x, tile.y, 1}, toIso);

   tile.x = new_pos.x;
   tile.y = new_pos.y;
}