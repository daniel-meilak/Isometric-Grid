#pragma once

// tile size and scale
constexpr int scaling{3};
constexpr int tileSize{32};
constexpr int scale = scaling*tileSize;

// Grid size
constexpr int gridWidth  = 12;
constexpr int gridHeight = 12;

// window variables
constexpr std::array<int,2> windowSize = {2 * scale*gridWidth, 2 * scale*gridHeight/2 };

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

// tile hovered over in last frame. -1 => no hover
constinit int lastHovered{-1};

// tile rise on mouse over
constexpr int tileRise{-10};