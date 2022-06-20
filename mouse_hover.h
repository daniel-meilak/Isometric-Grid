#pragma once 

#include<vector>

#include"constants.h"
#include"raylib.h"
#include"raymath.h"



Vector2 getGridCoord(const Vector2& mousePos){

   Vector3 onGrid = Vector3Transform({mousePos.x, mousePos.y, 1}, toGrid);

   return {onGrid.x, onGrid.y};
}

void mouseHover( std::vector<Rectangle>& tiles, const Vector2& mousePos){

   // undo last hover
   if (lastHovered>=0){ tiles[lastHovered].y -= tileRise; }

   // check for mouse hover
   Vector2 onGrid = getGridCoord( mousePos );
   float x_pos = onGrid.x/scale;
   float y_pos = onGrid.y/scale;

   // make sure mouse within grid boundaries
   if ( x_pos >= 0.0f && x_pos < gridWidth && y_pos >= 0.0f && y_pos < gridHeight){
      lastHovered = static_cast<int>(x_pos) + static_cast<int>(y_pos)*gridWidth;
      tiles[lastHovered].y += tileRise;
   }
   else {lastHovered = -1;}

   // debug info
   // DrawText(TextFormat("Mouse Actual Pos: %04.00f, %04.00f", mousePos.x, mousePos.y), 0,0,20, BLACK);
   // DrawText(TextFormat("Mouse Isomet Pos: %04.00f, %04.00f", onGrid.x, onGrid.y), 0,25,20, BLACK);
   DrawText(TextFormat("Mouse Coord:   %i, %i", static_cast<int>(onGrid.x/scale), (static_cast<int>(onGrid.y/scale))), 0,0,20, BLACK);
   DrawText(TextFormat("Index:   %i", lastHovered), 0,25,20, BLACK);

}
