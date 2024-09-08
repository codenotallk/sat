#include <sat.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SAT_SDL_SCREEN_WIDTH        480
#define SAT_SDL_SCREEN_HEIGHT       700


static void load_animation (sat_sdl_t *sdl, char *name, char *path, char *filename, bool type)
{
    char buffer [1024] = {0};
    snprintf (buffer, 1024 - 1, "%s/%s", path, filename);

    sat_sdl_animate_properties_t properties = 
    {
        .image_type = sat_sdl_image_type_png,
        .type = type == true ? sat_sdl_animate_type_background : sat_sdl_animate_type_sprite,
        .orientation = sat_sdl_background_orientation_horizontal,
        .sprites.dimension = 
        {
            .width = 50,
            .height = 37
        }
    };

    sat_status_t status = sat_sdl_animate_add (sdl, buffer, name, properties);
    assert (sat_status_get_result (&status) == true);
}


int main (int argc, char *argv[])
{
    sat_sdl_t *sdl;

    sat_status_t status = sat_sdl_init (&sdl, "Window Title", SAT_SDL_SCREEN_WIDTH, SAT_SDL_SCREEN_HEIGHT);
    assert (sat_status_get_result (&status) == true);

    load_animation (sdl, "background", argv[1], "space.png", true);
    load_animation (sdl, "hero", argv[1], "hero.png", false);
    
    sat_sdl_frame_position_t attack [] = 
    {
        {.row = 6, .column = 0},
        {.row = 6, .column = 1},
        {.row = 6, .column = 2},
        {.row = 6, .column = 3},
        {.row = 6, .column = 4},
    };

    sat_sdl_animate_add_states (sdl, "hero", "attack", attack, sizeof (attack) / sizeof (attack [0]));

    do 
    {
        status = sat_sdl_clear (sdl);
        assert (sat_status_get_result (&status) == true);

        status = sat_sdl_animate_draw (sdl, "background", NULL, (sat_sdl_coordinate_t){});
        assert (sat_status_get_result (&status) == true);

        status = sat_sdl_animate_draw (sdl, "hero", "attack", (sat_sdl_coordinate_t){.x = 0, .y = 0});
        assert (sat_status_get_result (&status) == true);

        status = sat_sdl_draw (sdl);
        assert (sat_status_get_result (&status) == true);

        status = sat_sdl_scan_events (sdl);

        usleep (100000);
    } while (sat_status_get_result (&status) == true);
    

    status = sat_sdl_close (sdl);
    assert (sat_status_get_result (&status) == true);

    return 0;
}