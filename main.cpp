#include<array>
#include<iostream>
#include<utility>
#include<vector>

#include <emscripten/emscripten.h>
#include"raylib.h"
#include"raymath.h"

#include"constants.h"
#include"textures.h"
#include"wave.h"
#include"grid.h"


// forward function declarations
void UpdateDrawFrame(void* data);

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   // initialize grid
   Grid grid(gridWidth,gridHeight);

   // initialize on-screen controlls
   Button button;

   std::pair<Grid,Button> input = std::make_pair(grid,button);
   void* data = &input;

   // game loop
   emscripten_set_main_loop_arg(UpdateDrawFrame,data,0,1);   

   textureStore.unloadAll();

   CloseWindow();

   return 0;
}

void UpdateDrawFrame(void* data){

   // unravel data
   std::pair<Grid,Button>* input = static_cast<std::pair<Grid,Button>*>(data);
   Grid& grid = input->first;
   Button& button = input->second;

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