#include <iostream>
#include <SDL2/SDL.h>
#include "res_path.h"


int main(int argc, char** argv) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* win = SDL_CreateWindow("Hellow SDL world!", 100, 100,
      640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError()
      << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError()
      << std::endl;
    SDL_Quit();
    return 1;
  }

  std::string imagePath = getResourcePath("Lesson1") + "cover.bmp";
  SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
  SDL_FreeSurface(bmp);
  if (tex == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateTextureFromSurface Error: " 
      << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  for (int i = 0; i < 3; ++i) {
    //First clear the renderer
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
  }

  char dummy;
  std::cout << "Enter any character to quit" << std::endl;
  std::cin >> dummy;
  SDL_Quit();
  return 0;
}
