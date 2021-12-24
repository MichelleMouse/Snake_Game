#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <mutex>
#include <vector>
#include "SDL.h"
#include "snake.hpp"

//So I can create a unique_ptr of SDL_Window
struct SDLWindowDeleter
{
  void operator()(SDL_Window* w) const
  {
    SDL_DestroyWindow(w);
  }
};

//So I can create a unique_ptr of SDL_Renderer
struct SDLRendererDeleter
{
  void operator()(SDL_Renderer* r) const
  {
    SDL_DestroyRenderer(r);
  }
};

class Renderer
{
public:
  //Constructors && Destructor
  Renderer(const std::size_t screen_w, const std::size_t screen_h, const std::size_t grid_w, const std::size_t grid_h);
  ~Renderer();

  //Typical behaviour methods
  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

private:
  //SDL Variables
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

  //Variables
  const std::size_t m_screen_w;
  const std::size_t m_screen_h;
  const std::size_t m_grid_w;
  const std::size_t m_grid_h;
  std::mutex m_mtx;
};

#endif