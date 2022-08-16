#include<array>
#include<iostream>
#include<utility>
#include<vector>

#include"raylib.h"

#include"constants.h"
#include"storage.h"
#include"button.h"
#include"grid.h"
#include"menu.h"

#ifdef PLATFORM_WEB
   #include <emscripten/emscripten.h>
#endif

// forward function declarations
void UpdateDrawFrame();

// global pointers
Grid* gridPtr;
Menu* menuPtr;

int main(){

   InitWindow(windowSize[0], windowSize[1], "Isometric Grid");

   // initialize grid
   Grid grid(gridWidth,gridHeight);
   gridPtr = &grid;

   // menu and buttons
   Menu menu(grid);
   menuPtr = &menu;

   std::pair<Grid*,Menu*> input = std::make_pair(&grid,&menu);
   void* data = &input;

   // game loop
   #ifdef PLATFORM_WEB
      emscripten_set_main_loop(UpdateDrawFrame,0,1);   
   #else
      SetTargetFPS(60);
      while(!WindowShouldClose()){
         UpdateDrawFrame();
      }
   #endif

   // unload all fonts and textures from GPU
   textureStore.unloadAll();
   fontStore.unloadAll();

   CloseWindow();

   return 0;
}

void UpdateDrawFrame(){

   // draw scene
   BeginDrawing();
   ClearBackground({144,101,254,0});

   // get current mouse position
   Vector2 mousePos = GetMousePosition();

   // draw grid to screen
   gridPtr->draw(mousePos);

   // display menu
   menuPtr->display(mousePos);

   EndDrawing();

}