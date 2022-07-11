#include<array>
#include<iostream>
#include<vector>

#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"storage.h"
#include"button.h"
#include"grid.h"
#include"menu.h"

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   SetTargetFPS(60);

   // initialize grid
   Grid grid(gridWidth,gridHeight);

   // menu and buttons
   Menu menu(grid);

   // game loop
   while (!WindowShouldClose()){

      // draw scene
      BeginDrawing();
      ClearBackground({144,101,254,0});

      // get current mouse position
      Vector2 mousePos = GetMousePosition();

      // draw grid to screen
      grid.draw(mousePos);

      // display menu
      menu.display(mousePos);

      EndDrawing();
   }

   // unload all fonts and textures from GPU
   textureStore.unloadAll();
   fontStore.unloadAll();

   CloseWindow();

   return 0;
}