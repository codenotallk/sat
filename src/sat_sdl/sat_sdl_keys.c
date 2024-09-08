#include <sat_sdl_keys.h>
#include <SDL2/SDL.h>

#define SAT_SDL_KEYS_GET_AMOUNT(x) (sizeof (x) / sizeof (x [0]))

#define SAT_SDL_KEYS_PRESSED        1
typedef struct 
{
    SDL_Keycode sdl_key;
    sat_sdl_key_t sat_key;
} sat_sdl_key_map_t;

static const sat_sdl_key_map_t keymap [] = 
{
    {.sdl_key = SDL_SCANCODE_UP,    .sat_key = sat_sdl_key_up   },
    {.sdl_key = SDL_SCANCODE_DOWN,  .sat_key = sat_sdl_key_down },
    {.sdl_key = SDL_SCANCODE_LEFT,  .sat_key = sat_sdl_key_left },
    {.sdl_key = SDL_SCANCODE_RIGHT, .sat_key = sat_sdl_key_right},
};

sat_sdl_key_t sat_sdl_key_get_by (const uint8_t *key)
{
    Uint8 *__key = (Uint8 *) key;
    sat_sdl_key_t sat_key = sat_sdl_key_none;

    for (uint16_t i = 0; i < SAT_SDL_KEYS_GET_AMOUNT (keymap); i++)
    {
        if (__key [keymap [i].sdl_key] == SAT_SDL_KEYS_PRESSED)
        {
            sat_key = keymap [i].sat_key;
            break;
        }
    }

    return sat_key;
}