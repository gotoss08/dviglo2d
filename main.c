#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sdl2/SDL.h>

#include "time.h"

#define TARGET_TICKS 120

float rand_float(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

int rand_int(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}

int main(int arch, char** argv) {

  srand(time(NULL));

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Log("SDL INITIALIZATION COMPLETE\n");

  SDL_Window* window = SDL_CreateWindow("dviglo2d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  double target_tick_time = 1000.0 / (double) TARGET_TICKS;

  int ticks = 0;
  Uint64 tick_time_start = SDL_GetPerformanceCounter();
  Uint64 tick_time_end = 0;

  double accum = 0.0;

  Uint64 seconds_timer = tick_time_start;

  double delta_time = 0.0;
  double lag = 0.0;

  int running = 1;

  while (running) {

    tick_time_start = SDL_GetPerformanceCounter();

    if (lag > 0) {
      Uint32 st = floor(lag);
      SDL_Log("sleep time %d", st);
      lag -= st;
      if (st > 0) SDL_Delay(st);
    }

    if (tick_time_start - seconds_timer >= SDL_GetPerformanceFrequency()) {
      SDL_Log("%d tps\n", ticks);
      ticks = 0;
      seconds_timer = tick_time_start;
    }

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        running = 0;
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          running = 0;
          break;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    tick_time_end = SDL_GetPerformanceCounter();

    ticks++;

    delta_time = (((double) (tick_time_end - tick_time_start)) * 1000.0) / (double) SDL_GetPerformanceFrequency();
    lag += target_tick_time - delta_time;

    SDL_Log("target tick time %f", target_tick_time);
    SDL_Log("delta time: %f", delta_time);
    SDL_Log("lag %f", lag);

  }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  SDL_Quit();
  
  return 0;
}
