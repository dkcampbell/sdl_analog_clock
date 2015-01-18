#include "Clock.hpp"

#include <string>


// Really basic Analog clock using SDL. If this was to be cleaned up getting
// rid of the hardcoded values for Window size would be good.

int main(int argc, char **argv) 
{
  Clock clock;

  if(!clock.init("Analog Clock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN)) {
    return -1;
  }

  while (clock.running()) {
    clock.render();
    clock.update();
    clock.handleEvents();
  }

  clock.clean(); 
  return 0;
}
