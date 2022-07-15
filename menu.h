#pragma once

#include<cstring>
#include<string>
#include<vector>

#include"raylib.h"

#include"button.h"
#include"constants.h"
#include"grid.h"
#include"section.h"
#include"storage.h"

// Menu of sections
struct Menu {

   // alpha_beta font by Brian Kent (AEnigma)
   Font& font{fontStore.add("fonts/alpha_beta.png")};

   // grid
   Grid& grid;

   std::vector<Section> sections;
   std::vector<Button> buttons;

   // menu origin
   float x{32.0f};
   float y{0.0f};

   // menu height (increases on adding sections)
   float height{0.0f};

   // menu size multiplier
   float sizeMulti{3.0f};

   Menu(Grid& grid);

   // add a simple section to menu, which acts as one large button
   void addSectionBasic(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> func);

   // add a section with inc. and decr. buttons
   void addSectionRange(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> incr, std::function<void(Grid&)> decr);

   // move menu position
   void move(float newX, float newY);

   void display(const Vector2& mousePos){
      for (auto& section : sections){ section.display(mousePos); }
   };

};

Menu::Menu(Grid& grid): grid(grid){

   // wave on/off
   addSectionBasic(sectionType::top, "Wave: ", &grid.waveState, 0.6f*font.baseSize, 1.0f, &Grid::waveSwitch);

   // speed
   addSectionRange(sectionType::mid, "Speed: ", &grid.speed, 0.6*font.baseSize, 1.0f, &Grid::incSpeed, &Grid::decSpeed);

   // amplitude
   addSectionRange(sectionType::bot, "Amplitude: ", &grid.amplitude, 0.6*font.baseSize, 1.0f, &Grid::incAmplitude, &Grid::decAmplitude);

   // centre menu
   move(x, windowSize[1]/2.0f - height/2.0f);

}

// add a simple section to menu, which acts as one large button
void Menu::addSectionBasic(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> onClick){

   // create section and button
   Section section{font, type, false, x, height, message, param, fontSize, spacing, sizeMulti};
   Button button{"sprites/menu.png", type, x, height, 3.0f, 3.0f, sizeMulti, onClick, grid};

   // increase menu height by section height
   height += section.bounds.height;

   // link together and add to menu
   section.buttons.push_back(std::move(button));
   sections.push_back(std::move(section));
}

void Menu::addSectionRange(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> incr, std::function<void(Grid&)> decr){

   // create section and buttons
   Section section{font, type, true, x, height, message, param, fontSize, spacing, sizeMulti};
   Button  left{"sprites/left-arrow.png" , sectionType::top, x + (3*sizeMulti) , height + (5*sizeMulti), 3.0f, 1.0f, sizeMulti, decr, grid};
   Button right{"sprites/right-arrow.png", sectionType::top, x + (82*sizeMulti), height + (5*sizeMulti), 3.0f, 1.0f, sizeMulti, incr, grid};

   // increase menu height by section height
   height += section.bounds.height;

   // link together and add to menu
   section.buttons.push_back(std::move(left));
   section.buttons.push_back(std::move(right));
   sections.push_back(std::move(section));
}

void Menu::move(float newX, float newY){

   float xDiff=newX-x, yDiff=newY-y;

   // move menu
   x = newX;
   y = newY;

   // move sections
   for (auto& section : sections){
      section.move(xDiff, yDiff);
   }
}