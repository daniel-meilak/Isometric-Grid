#pragma once

// tile size and scale
constexpr int scaling{3};
constexpr int tileSize{32};
constexpr int scale = scaling*tileSize;

// Grid size
constexpr int gridWidth{8};
constexpr int gridHeight{8};

// Textures
constexpr int maxTextures{10};

// window variables
constexpr std::array<int,2> windowSize = {2 * scale*gridWidth, 2 * scale*gridHeight/2 };

// enum for buttons and menu
enum sectionType {top=0, mid=1, bot=2};

// matrix to transform into isometric + centre grid 
constexpr Matrix toIso{
   0.5f , -0.5f, -scale/2.0f+windowSize[0]/2.0f, 0.0f,
   0.25f, 0.25f,          gridHeight*scale/4.0f, 0.0f,
   0.0f ,  0.0f,                           1.0f, 0.0f,
   0.0f ,  0.0f,                           0.0f, 1.0f
};

// matrix to transform from centred isometric grid
constexpr Matrix toGrid{
   1.0f , 2.0f, -windowSize[0]/2.0f - gridHeight*scale/2.0f, 0.0f,
   -1.0f, 2.0f, -gridHeight*scale/2.0f + windowSize[0]/2.0f, 0.0f,
   0.0f , 0.0f,                                        1.0f, 0.0f,
   0.0f , 0.0f,                                        0.0f, 1.0f
};