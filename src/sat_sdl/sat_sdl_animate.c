#include <sat_sdl_animate.h>

sat_status_t sat_sdl_animate_load (sat_sdl_animate_t *object, sat_sdl_render_t *render, sat_sdl_image_t *image)
{
    return sat_sdl_texture_create (&object->texture, render, image);
}

void sat_sdl_animate_unload (sat_sdl_animate_t *object)
{
    return sat_sdl_texture_destroy (&object->texture);
}