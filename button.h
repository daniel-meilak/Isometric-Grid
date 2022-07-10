#pragma once

#include<algorithm>
#include<array>
#include<cmath>
#include<numeric>
#include<vector>

#include"raylib.h"

#include"constants.h"
#include"grid.h"
#include"textures.h"

struct Button {

   Texture2D& texture;
   Rectangle source{};
   Rectangle bounds{};

   int state{0}; // 0 normal, 1 hover, 2 click

   Button(): texture(textureStore.add("sprites/button.png")){

      // set size
      source.width = texture.width/3.0f;
      source.height = texture.height/2.0f;

      // set bounds
      bounds = {32,windowSize[1]/4,source.width*2,source.height*2};
   };

   void display(Grid& grid, const Vector2& mousePos);
};

void Button::display(Grid& grid, const Vector2& mousePos){

   if (CheckCollisionPointRec(mousePos, bounds)){

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ state = 2; }
      else { state = 1; }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
         source.y = std::fmod(source.y + texture.height/2, texture.height);
         grid.transitioning = grid.waveState ? -1 : 1;
         grid.waveState = !grid.waveState;
      }
   }
   else { state = 0; }

   source.x = state*texture.width/3;
   
   //DrawTextureRec(button.texture, button.source, {}, WHITE);
   DrawTexturePro(texture, source, bounds, {}, 0.0f, WHITE);
}

