#pragma once

#include<array>
#include<cstdlib>
#include<iostream>
#include<string>
#include<unordered_map>

#include"raylib.h"


struct TextureStorage{
   
   Texture2D& add(const char* filename){

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

   void unloadAll(){

      for (int i=0; i<=index; i++){ 
         UnloadTexture(textures[i]); 
      }
   }

private:

   int index{-1};
   std::array<Texture2D,maxTextures> textures;

   std::unordered_map<std::string,int> textureIndex;

} textureStore;