#pragma once

#include<string>
#include<vector>

#include"raylib.h"


struct TextureStorage{
   
   void add(Texture2D& texture){
      textures.push_back(&texture);
   }

   void unloadAll(){
      for (auto& texture : textures){ UnloadTexture(*texture); }
   }

private:
   std::vector<Texture2D*> textures;

} textureStore;