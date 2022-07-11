#pragma once

#include<cstring>
#include<string>
#include<variant>
#include<vector>

#include"raylib.h"

#include"button.h"
#include"button_functions.h"
#include"constants.h"
#include"grid.h"
#include"storage.h"

using Param = std::variant<bool*,int*,float*>;

// Section of Menu, contains one or more buttons
struct Section {

   // reference to font in fontStorage
   Font& font;

   // Top, middle or bottom of menu (affects texture)
   sectionType type;

   // Has texture (false if button takes up full size)
   bool hasTexture;

   // Texture
   Texture2D& texture{textureStore.add("sprites/menu.png")};
   Rectangle source{0.0f, 0.0f, texture.width/3.0f, texture.height/3.0f};
   Rectangle bounds{source};

   // Static message
   std::string message;

   // Variable grid property, displayed next to message
   Param gridProperty;
   std::string propertyMessage{};

   // message position (w.r.t section origin)
   Vector2 offset;

   // Message stle
   float fontSize;
   float spacing;

   // associated buttons
   std::vector<Button> buttons;

   Section(Font& font, sectionType type, bool hasTexture, float x, float y, std::string message, Param gridProperty, float fontSize, float spacing, float sizeMulti);

   void setMessage();

   void display(const Vector2& mousePos);

   void move(float xDiff, float yDiff);
};

Section::Section(Font& font, sectionType type, bool hasTexture, float x, float y, std::string message, Param gridProperty, float fontSize, float spacing, float sizeMulti):
   font(font), type(type), hasTexture(hasTexture), message(message), gridProperty(gridProperty), fontSize(fontSize*sizeMulti), spacing(spacing*sizeMulti){
      
      source.y = static_cast<int>(type)*source.height;
      bounds.x = x;
      bounds.y = y;
      bounds.width  *= sizeMulti;
      bounds.height *= sizeMulti;
};

void Section::setMessage(){
   if (std::holds_alternative<bool*>(gridProperty)){ propertyMessage = *std::get<bool*>(gridProperty) ? "On" : "Off"; }
   else if (std::holds_alternative<int*>(gridProperty)){ propertyMessage = std::to_string(*std::get<int*>(gridProperty)); }
   else { propertyMessage = std::to_string(*std::get<float*>(gridProperty)); }
}

void Section::display(const Vector2& mousePos){

   // update property message
   setMessage();

   // only display background if required
   if (hasTexture){ DrawTexturePro(texture, source, bounds, {}, 0.0f, WHITE); }

   // display all associated buttons
   for (auto& button : buttons){
      button.display(mousePos);
   }

   // display text
   std::string fullMessage = message + propertyMessage;
   
   // offset to centre text
   Vector2 textSize = MeasureTextEx(font, fullMessage.c_str(), this->fontSize, this->spacing);
   offset = {bounds.width/2.0f - textSize.x/2.0f, bounds.height/2.0f - textSize.y/2.0f};

   DrawTextEx(font, fullMessage.c_str(), {bounds.x+offset.x, bounds.y+offset.y}, fontSize, spacing, WHITE);
}

void Section::move(float xDiff, float yDiff){

   // move section
   bounds.x += xDiff;
   bounds.y += yDiff;

   // move buttons
   for (auto& button : buttons){
      button.bounds.x += xDiff;
      button.bounds.y += yDiff;
   }
}


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
   addSectionBasic(sectionType::top, "Wave: ", &grid.waveState, 0.6f*font.baseSize, 1.0f, waveSwitch);

   // speed
   addSectionRange(sectionType::mid, "Speed: ", &grid.speed, 0.6*font.baseSize, 1.0f, speedUp, speedDown);

   // amplitude
   addSectionRange(sectionType::bot, "Amplitude: ", &grid.amplitude, 0.6*font.baseSize, 1.0f, amplitudeUp, amplitudeDown);

   // centre menu
   move(x, windowSize[1]/2.0f - height/2.0f);

}

// add a simple section to menu, which acts as one large button
void Menu::addSectionBasic(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> func){

   // create section and button
   Section section{font, type, false, x, height, message, param, fontSize, spacing, sizeMulti};
   Button button{"sprites/menu.png", type, x, height, 3.0f, 3.0f, sizeMulti, std::bind(func, std::ref(grid))};

   // increase menu height by section height
   height += section.bounds.height;

   // link together and add to menu
   section.buttons.push_back(std::move(button));
   sections.push_back(std::move(section));
}

void Menu::addSectionRange(sectionType type, std::string message, Param param, float fontSize, float spacing, std::function<void(Grid&)> incr, std::function<void(Grid&)> decr){

   // create section and buttons
   Section section{font, type, true, x, height, message, param, fontSize, spacing, sizeMulti};
   Button  left{"sprites/left-arrow.png" , sectionType::top, x + (3*sizeMulti) , height + (5*sizeMulti), 3.0f, 1.0f, sizeMulti, std::bind(decr, std::ref(grid))};
   Button right{"sprites/right-arrow.png", sectionType::top, x + (82*sizeMulti), height + (5*sizeMulti), 3.0f, 1.0f, sizeMulti, std::bind(incr, std::ref(grid))};

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