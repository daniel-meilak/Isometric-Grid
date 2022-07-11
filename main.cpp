#include<array>
#include<iostream>
#include<utility>
#include<vector>

#include <emscripten/emscripten.h>
#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"storage.h"
#include"button.h"
#include"grid.h"
#include"menu.h"

// forward function declarations
void UpdateDrawFrame(void* data);

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   // initialize grid
   Grid grid(gridWidth,gridHeight);

   // menu and buttons
   Menu menu(grid);

   std::pair<Grid,Menu> input = std::make_pair(grid,menu);
   void* data = &input;

   // game loop
   emscripten_set_main_loop_arg(UpdateDrawFrame,data,0,1);   

   // unload all fonts and textures from GPU
   textureStore.unloadAll();
   fontStore.unloadAll();

   CloseWindow();

   return 0;
}

void UpdateDrawFrame(void* data){

   // unravel data
   std::pair<Grid,Menu>* input = static_cast<std::pair<Grid,Menu>*>(data);
   Grid& grid = input->first;
   Menu& menu = input->second;

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