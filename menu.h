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


struct Section {

   Font& font;

   // Top, middle or bottom of menu (affects texture)
   sectionType type;

   // Has texture (false if button takes up full size)
   bool hasTexture;

   // Texture
   Texture2D& texture{textureStore.add("sprites/menu.png")};
   Rectangle source{0.0f, 0.0f, texture.width/3.0f, texture.height/3.0f};
   Rectangle bounds{source};

   // message
   std::string message;

   // seciton property
   using variant = std::variant<bool*,int*,float*>;
   variant gridProperty;
   std::string propertyMessage{};

   // message position (w.r.t menu postion)
   Vector2 offset;

   // size multiplier
   float fontSize;

   // spacing
   float spacing;

   // associated buttons
   std::vector<Button> buttons;

   Section(Font& font, sectionType type, bool hasTexture, float x, float y, std::string message, variant gridProperty, float fontSize, float spacing, float scale):
      font(font), type(type), hasTexture(hasTexture), message(message), gridProperty(gridProperty), fontSize(fontSize*scale), spacing(spacing*scale){
         
         source.y = static_cast<int>(type)*source.height;
         bounds.x = x;
         bounds.y = y;
         bounds.width  *= scale;
         bounds.height *= scale;
   };

   void setMessage(){
      if (std::holds_alternative<bool*>(gridProperty)){ propertyMessage = *std::get<bool*>(gridProperty) ? "On" : "Off"; }
      else if (std::holds_alternative<int*>(gridProperty)){ propertyMessage = std::to_string(*std::get<int*>(gridProperty)); }
      else { propertyMessage = std::to_string(*std::get<float*>(gridProperty)); }
   }

   void display(const Vector2& mousePos){

      // update property message
      setMessage();

      // display all associated buttons
      for (auto& button : buttons){
         button.display(mousePos);
      }

      // only display background if required
      if (hasTexture){ DrawTexturePro(texture, source, bounds, {}, 0.0f, WHITE); }

      // display text
      std::string fullMessage = message + propertyMessage;
      
      // offset to centre text
      Vector2 textSize = MeasureTextEx(font, fullMessage.c_str(), this->fontSize, this->spacing);
      offset = {bounds.width/2.0f - textSize.x/2.0f, bounds.height/2.0f - textSize.y/2.0f};

      DrawTextEx(font, fullMessage.c_str(), {bounds.x+offset.x, bounds.y+offset.y}, fontSize, spacing, WHITE);
   }
};

struct Menu {

   // alpha_beta font by Brian Kent (AEnigma)
   Font& font{fontStore.add("fonts/alpha_beta.png")};

   // grid
   Grid& grid;

   std::vector<Section> sections;
   std::vector<Button> buttons;

   // menu x-pos
   float x{32.0f};

   // menu height (increases on adding sections)
   float height{windowSize[1]/4.0f};

   // menu size multiplier
   float sizeMulti{3.0f};

   void display(const Vector2& mousePos);

   Menu(Grid& grid): grid(grid){

      // wave on/off
      Section waveOnOff{font, sectionType::top, false, x, height, "Wave: ", &grid.waveState, 0.6f*font.baseSize, 1.0f, sizeMulti};
      Button waveButton{"sprites/menu.png", sectionType::top, x, height, sizeMulti, std::bind(waveSwitch, std::ref(grid))};
      waveOnOff.buttons.push_back(std::move(waveButton));
      sections.push_back(std::move(waveOnOff));
      height += waveOnOff.bounds.height;

      // sections.push_back(Section(font, sectionType::top, false, x, height, "Wave: off", 0.6f*font.baseSize, 1.0f, sizeMulti, height));
      // buttons.push_back(Button("sprites/menu.png",sectionType::top, x, height, sizeMulti));
      
      sections.push_back(Section(font, sectionType::mid,  true, x, height, "Amplitude: ", &grid.amplitude, 0.6f*font.baseSize, 1.0f, sizeMulti));
      height += waveOnOff.bounds.height;

      sections.push_back(Section(font, sectionType::bot,  true, x, height, "Amplitude: ", &grid.amplitude, 0.6f*font.baseSize, 1.0f, sizeMulti));
   }   

};

void Menu::display(const Vector2& mousePos){

   for (auto& section : sections){ section.display(mousePos); }

}



