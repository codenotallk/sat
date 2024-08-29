#ifndef SAT_SDL_ANIMATE_H_
#define SAT_SDL_ANIMATE_H_

#include <sat_sdl_texture.h>
#include <sat_sdl_types.h>

typedef struct 
{
    sat_sdl_texture_t texture;
    sat_sdl_animate_type_t type;
    sat_sdl_background_orientation_t orientation;
    int32_t offset;

} sat_sdl_animate_t;

sat_status_t sat_sdl_animate_load (sat_sdl_animate_t *object, sat_sdl_render_t *render, sat_sdl_image_t *image);
void sat_sdl_animate_unload (sat_sdl_animate_t *object);

#endif/* SAT_SDL_ANIMATE_H_ */
