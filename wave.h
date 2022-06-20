#pragma once

#include<algorithm>
#include<array>
#include<cmath>
#include<numeric>
#include<vector>

#include"raylib.h"

#include"constants.h"

void wave_start(std::vector<Rectangle>& tiles, int& grid_pos);
void wave_end(std::vector<Rectangle>& tiles, int& grid_pos);

bool button_on{false};
int wave_amplitude{1};
float wave_length{0.01};
float dt{0};
int wave_speed{0};

struct Button {

   Texture2D texture;
   Rectangle source{};
   Rectangle bounds{};

   Button(const Texture2D& texture): texture(texture){
      source  = {0.0f,0.0f,texture.width/3.0f,texture.height/2.0f};
      bounds  = {32,windowSize[1]/4,source.width*2,source.height*2};
   }
};

void waveButton(std::vector<Rectangle>& tiles, const Vector2& mousePos, const Texture2D& texture){

   static Button button(texture);
   int state{0}; // 0 normal, 1 hover, 2 click

   // DrawText(TextFormat("Mouse Actual Pos: %04.00f, %04.00f", mousePos.x, mousePos.y), 0,50,20, BLACK);
   // DrawText(TextFormat("Box Pos: %04.00f, %04.00f", button.bounds.x, button.bounds.y), 0,75,20, BLACK);

   if (CheckCollisionPointRec(mousePos, button.bounds)){

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ state = 2; }
      else { state = 1; }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
         button.source.y = std::fmod(button.source.y + button.texture.height/2, button.texture.height);
         button_on = !button_on;
      }
   }
   else { state = 0; }

   //wave(tiles, button.on);

   button.source.x = state*button.texture.width/3;
   
   //DrawTextureRec(button.texture, button.source, {}, WHITE);
   DrawTexturePro(texture, button.source, button.bounds, {}, 0.0f, WHITE);
}

float waveOffset(const Rectangle& tile){

   return button_on ? wave_amplitude*std::sin((dt + tile.x + tile.y)*wave_length) : 0;

}