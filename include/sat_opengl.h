#ifndef SAT_OPENGL_H_
#define SAT_OPENGL_H_

#include <sat_status.h>
#include <stdint.h>

#include <sat_opengl_types.h>

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
sat_status_t sat_opengl_create_program (sat_opengl_t *object, const char *name);
sat_status_t sat_opengl_add_shader_to_program (sat_opengl_t *object, const char *name, sat_opengl_shader_type_t type, const char *filename);
sat_status_t sat_opengl_compile_program (sat_opengl_t *object, const char *name);
sat_status_t sat_opengl_close (sat_opengl_t *object);

#endif/* SAT_OPENGL_H_ */
