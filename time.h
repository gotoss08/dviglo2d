#ifndef TIME_H_
#define TIME_H_

#include <sdl2/sdl.h>

#define WORST_CLOCK_ACCURACY 12

int accurate_delay(int ticks)
{
    int funcstart, delay;

    if (ticks <= 0)
        return 0;

    funcstart = SDL_GetTicks();

    if (ticks >= WORST_CLOCK_ACCURACY) {
        delay = (ticks - 2) - (ticks % WORST_CLOCK_ACCURACY);
        if (delay >= WORST_CLOCK_ACCURACY) {
            SDL_Delay(delay);
        }
    }

    do {
        delay = ticks - (SDL_GetTicks() - funcstart);
    } while (delay > 0);

    return SDL_GetTicks() - funcstart;
}

#endif // TIME_H_
