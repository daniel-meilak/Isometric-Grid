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

   Texture2D texture{LoadTexture("sprites/button.png")};
   Rectangle source{0.0f,0.0f,texture.width/3.0f,texture.height/2.0f};
   Rectangle bounds{32,windowSize[1]/4,source.width*2,source.height*2};

   int state{0}; // 0 normal, 1 hover, 2 click

   Button(){

      // add button texture to store for easier unloading
      textureStore.add(texture);
   };

   void display(Grid& grid, const Vector2& mousePos);
};

void Button::display(Grid& grid, const Vector2& mousePos){

   if (CheckCollisionPointRec(mousePos, bounds)){

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){ state = 2; }
      else { state = 1; }

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
         source.y = std::fmod(source.y + texture.height/2, texture.height);
         grid.waveState = !grid.waveState;
      }
   }
   else { state = 0; }

   source.x = state*texture.width/3;
   
   //DrawTextureRec(button.texture, button.source, {}, WHITE);
   DrawTexturePro(texture, source, bounds, {}, 0.0f, WHITE);
}

