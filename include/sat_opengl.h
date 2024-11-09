#ifndef SAT_OPENGL_H_
#define SAT_OPENGL_H_

#include <sat_status.h>
#include <stdint.h>

typedef struct sat_opengl_t sat_opengl_t;

typedef struct 
{
    struct 
    {
        uint16_t width;
        uint16_t height;
        const char *title;
    } window;

} sat_opengl_args_t;

sat_status_t sat_opengl_create (sat_opengl_t **object, sat_opengl_args_t *args);
sat_status_t sat_opengl_run (sat_opengl_t *object);
sat_status_t sat_opengl_close (sat_opengl_t *object);

#endif/* SAT_OPENGL_H_ */
