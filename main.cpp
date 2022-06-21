#include<array>
#include<iostream>
#include<vector>

#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"textures.h"
#include"wave.h"
#include"grid.h"

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   SetTargetFPS(60);

   // initialize grid
   Grid grid(gridWidth,gridHeight);

   // initialize on-screen controlls
   Button button;

   // game loop
   while (!WindowShouldClose()){

      // draw scene
      BeginDrawing();
      ClearBackground({144,101,254,0});

      // get current mouse position
      Vector2 mousePos = GetMousePosition();

      // check for and animate mouse hover over tile
      grid.mouseHover(mousePos);

      // get user input (wave controls)
      grid.getInput();

      // draw grid to screen
      grid.draw();

      // draw button
      button.display(grid, mousePos);

      EndDrawing();
   }

   textureStore.unloadAll();

   CloseWindow();

   return 0;
}