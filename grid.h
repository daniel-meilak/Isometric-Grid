#pragma once

#include<vector>

#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"textures.h"
#include"wave.h"

struct Grid{

   int width;
   int height;

   Texture2D texture{LoadTexture("sprites/tile.png")};
   Rectangle source{0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
   
   std::vector<Rectangle> tiles;

   int lastHovered{-1};
   int tileRise{-10};

   // wave properties
   bool waveState{false};
   int amplitude{0};
   int speed{5};
   float wavelength{0.01};
   float dt{0};

   Grid(int width, int height);

   void mouseHover(const Vector2& mousePos);
   float waveOffset(const Rectangle& tile);
   void getInput();
   void draw();
};

Grid::Grid(int width, int height): width(width), height(height){

   // add tile texture to store for easier unloading
   textureStore.add(texture);

   // create grid with initial positions
   Vector3 temp;
   for (int j=0; j<height; j++){
      for (int i=0; i<width; i++){
         temp = Vector3Transform({static_cast<float>(i)*scale, static_cast<float>(j)*scale, 1}, toIso);

         tiles.push_back({temp.x,temp.y,scale,scale});
      }
   }
}

void Grid::mouseHover(const Vector2& mousePos){

   // turn off mouse hover during wave state
   if (waveState){ return; }

   // undo last hover
   if (lastHovered>=0){ tiles[lastHovered].y -= tileRise; }

   // check for mouse hover
   Vector3 onGrid = Vector3Transform({mousePos.x, mousePos.y, 1}, toGrid);
   float x_pos = onGrid.x/scale;
   float y_pos = onGrid.y/scale;

   // make sure mouse within grid boundaries
   if ( x_pos >= 0.0f && x_pos < width && y_pos >= 0.0f && y_pos < height){
      lastHovered = static_cast<int>(x_pos) + static_cast<int>(y_pos)*width;
      tiles[lastHovered].y += tileRise;
   }
   else {lastHovered = -1;}

   // debug info
   DrawText(TextFormat("Mouse Coord:   %i, %i", static_cast<int>(onGrid.x/scale), (static_cast<int>(onGrid.y/scale))), 0,0,20, BLACK);
   DrawText(TextFormat("Index:   %i", lastHovered), 0,25,20, BLACK);
}

void Grid::draw(){

   for (const auto& tile : tiles){
      DrawTexturePro(texture, source, {tile.x, tile.y+waveOffset(tile), tile.width, tile.height}, {}, 0.0f, WHITE);
   }

   // wave state info
   if (waveState){
      DrawText(TextFormat("Wave Amplitude:   %i", amplitude), 0,0,20, BLACK);
      DrawText(TextFormat("Wave length:   %01.04f", wavelength), 0,25,20, BLACK);
      DrawText(TextFormat("Wave Speed:   %i", speed), 0,50,20, BLACK);
   }
}

void Grid::getInput(){
   
   if (waveState){
      if (IsKeyDown(KEY_UP    )){ amplitude++;          }
      if (IsKeyDown(KEY_DOWN  )){ amplitude--;          }
      if (IsKeyDown(KEY_LEFT  )){ wavelength += 0.00001;}
      if (IsKeyDown(KEY_RIGHT )){ wavelength -= 0.00001;}
      if (IsKeyDown(KEY_SPACE )){ dt += speed;          }

      if (IsKeyPressed(KEY_PERIOD)){ speed++;     }
      if (IsKeyPressed(KEY_COMMA )){ speed--;     }      
   }
}

float Grid::waveOffset(const Rectangle& tile){

   return waveState ? amplitude*std::sin((dt + tile.x + tile.y)*wavelength) : 0;

}

