#ifndef SAT_SDL_KEYS_H_
#define SAT_SDL_KEYS_H_

#include <stdint.h>

typedef enum 
{
    sat_sdl_key_none,
    sat_sdl_key_up,
    sat_sdl_key_down,
    sat_sdl_key_left,
    sat_sdl_key_right
} sat_sdl_key_t;

sat_sdl_key_t sat_sdl_key_get_by (const uint8_t *key); 

#endif/* SAT_SDL_KEYS_H_ */
