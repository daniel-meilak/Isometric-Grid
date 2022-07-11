#pragma once

#include<array>
#include<cstdlib>
#include<iostream>
#include<string>
#include<type_traits>
#include<unordered_map>

#include"raylib.h"

template <typename T>
struct Storage{
   
   T& add(const char* filename);

   void unloadAll();

private:

   int index{-1};
   std::array<T,maxTextures> textures;

   std::unordered_map<std::string,int> textureIndex;

};

// Crate stores in global scope
Storage<Texture2D> textureStore;
Storage<Font> fontStore;

// Texture Storage
template<>
Texture2D& Storage<Texture2D>::add(const char* filename){

   // check if texture is already loaded
   if (textureIndex.contains(filename)){
      return textures[textureIndex.at(filename)];
   }
   // else add new texture
   else{

      // increment texture index and check if limit reached
      if (static_cast<size_t>(++index) == textures.size()){
         std::cerr << "Texture storage limit reached. Cannot load \"" << filename << "\".\n";
         std::exit(EXIT_FAILURE);
      }

      textures[index] = LoadTexture(filename);

      // add to uniqueTextures in case of future requests
      textureIndex[filename] = index;

      return textures[index];
   }
}

template<>
void Storage<Texture2D>::unloadAll(){

   for (int i=0; i<=index; i++){ 
      UnloadTexture(textures[i]); 
   }
}


// Font Storage
template<>
Font& Storage<Font>::add(const char* filename){

   // check if texture is already loaded
   if (textureIndex.contains(filename)){
      return textures[textureIndex.at(filename)];
   }
   // else add new texture
   else{

      // increment texture index and check if limit reached
      if (static_cast<size_t>(++index) == textures.size()){
         std::cerr << "Font storage limit reached. Cannot load \"" << filename << "\".\n";
         std::exit(EXIT_FAILURE);
      }

      textures[index] = LoadFont(filename);

      // add to uniqueTextures in case of future requests
      textureIndex[filename] = index;

      return textures[index];
   }
}

template<>
void Storage<Font>::unloadAll(){

   for (int i=0; i<=index; i++){ 
      UnloadFont(textures[i]); 
   }
}