#include <sat.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define SAT_SDL_SCREEN_WIDTH        480
#define SAT_SDL_SCREEN_HEIGHT       700


static void load_animation (sat_sdl_t *sdl, char *name, char *path, char *filename)
{
    char buffer [1024] = {0};
    snprintf (buffer, 1024 - 1, "%s/%s", path, filename);

    sat_sdl_animate_properties_t properties = 
    {
        .image_type = sat_sdl_image_type_png,
        .type = sat_sdl_animate_type_background,
        .orientation = sat_sdl_background_orientation_vertical
    };

    sat_status_t status = sat_sdl_animate_add (sdl, buffer, name, properties);
    assert (sat_status_get_result (&status) == true);
}


int main (int argc, char *argv[])
{
    sat_sdl_t *sdl;

    sat_status_t status = sat_sdl_init (&sdl, "Window Title", SAT_SDL_SCREEN_WIDTH, SAT_SDL_SCREEN_HEIGHT);
    assert (sat_status_get_result (&status) == true);

    load_animation (sdl, "background", argv[1], "space.png");

    while (true)
    {
        status = sat_sdl_animate_draw (sdl, "background");
        assert (sat_status_get_result (&status) == true);

        status = sat_sdl_draw (sdl);
        assert (sat_status_get_result (&status) == true);
    }
    

    status = sat_sdl_close (sdl);
    assert (sat_status_get_result (&status) == true);

    return 0;
}