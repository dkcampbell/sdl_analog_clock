#include "Clock.hpp"

#include <ctime>
#include <cmath>
#include <SDL2/SDL_image.h>

bool Clock::init(std::string title, int xpos, int ypos, int height, int width, int flags)
{
  // SDL_INIT_EVERYTHING was failing on Windows because I compiled it without
  // Haptic feedback support
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) >= 0) {
    m_pWindow = SDL_CreateWindow(title.c_str(), xpos, ypos, height, width, flags);

    if (m_pWindow != nullptr) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
      m_bRunning = true;
    }
  } else {
    return false;
  }

  // Clock Face
  SDL_Surface* pTempSurface = IMG_Load("assets/clock.png");
  m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  return true;
}

void Clock::render()
{

  std::time_t result = std::time(nullptr);
  std::tm* now = std::localtime(&result);

  double hour = (double) now->tm_hour;
  double minute = (double) now->tm_min;
  double second = (double) now->tm_sec;

  // Clear the background and place the clock face
  SDL_RenderClear(m_pRenderer);
  SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, nullptr);


  // This is all really silly math to draw lines using a bunch of points.
  // SDL doesn't support rotating basic shapes without the gfx library.
  // I didn't want to take the time to build that and get it working on 
  // Windows.

  // Draw the Hour hand in red
  double hourAngle = (hour/12.0)*(2*M_PI) - M_PI/2.0 + M_PI/8.0*(minute/60.0); 
  SDL_SetRenderDrawColor(m_pRenderer, 0xff, 0x00, 0x00, 0x00); 
  for (int i = 0; i < 128; ++i) {
    SDL_RenderDrawPoint(m_pRenderer, 256 + i*cos(hourAngle), 256 + i*sin(hourAngle));
  }

  // Draw the minute hand in green
  double minuteAngle = (minute/60.0)*(2*M_PI) - M_PI/2.0;
  SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0xff, 0x00, 0x00); 
  for (int i = 0; i < 256; ++i) {
    SDL_RenderDrawPoint(m_pRenderer, 256 + i*cos(minuteAngle), 256 + i*sin(minuteAngle));
  }

  // Draw the second hand in blue
  double secondAngle = (second/60.0)*(2*M_PI) - M_PI/2.0;
  SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0xff, 0x00); 
  for (int i = 0; i < 256; i++) {
    SDL_RenderDrawPoint(m_pRenderer, 256 + i*cos(secondAngle), 256 + i*sin(secondAngle));
  }

  // Render Scene
  SDL_RenderPresent(m_pRenderer);
}

void Clock::update() 
{
}

void Clock::handleEvents() 
{
  SDL_Event event;
  if (SDL_WaitEventTimeout(&event, 500)) {
    switch (event.type) {
    case SDL_QUIT:
      m_bRunning = false;
      break;
    default:
      break;
    }
  }
}

void Clock::clean() 
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}
