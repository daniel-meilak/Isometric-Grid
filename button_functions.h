#pragma once

#include"grid.h"

void waveSwitch(Grid& grid){
   grid.transitioning = grid.waveState ? -1 : 1;
   grid.waveState = !grid.waveState;
}

void amplitudeUp(Grid& grid){
   grid.amplitude++;
}

void ampitudeDown(Grid& grid){
   grid.amplitude--;
}

void wavelengthUp(Grid& grid){
   grid.wavelength += 0.00001;
}

void wavelengthDown(Grid& grid){
   grid.wavelength -= 0.00001;
}