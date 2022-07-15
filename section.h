#pragma once

#include<vector>

#include"button.h"
#include"constants.h"
#include"storage.h"

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