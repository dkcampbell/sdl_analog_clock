#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SDL2/SDL.h>

class Clock 
{
  public:
    Clock() : m_bRunning{false} {}
    ~Clock() {}

    bool init(std::string title, int xpos, int ypos, int height, int width, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() { return m_bRunning; }
  private:
    bool m_bRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    SDL_Texture* m_pTexture;
};


#endif

