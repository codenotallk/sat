#ifndef SAT_OPENGL_PROGRAM_H_
#define SAT_OPENGL_PROGRAM_H_

#include <sat_status.h>
#include <sat_array.h>
#include <sat_opengl_shader.h>

typedef struct 
{
    unsigned int id;
    const char *name;
    sat_array_t *shaders;

} sat_opengl_program_t;

typedef struct 
{
    const char *name;

} sat_opengl_program_args_t;

sat_status_t sat_opengl_program_create (sat_opengl_program_t *object, sat_opengl_program_args_t *args);
sat_status_t sat_opengl_program_shader_add (sat_opengl_program_t *object, sat_opengl_shader_t *shader);
sat_status_t sat_opengl_program_link (sat_opengl_program_t *object); 
sat_status_t sat_opengl_program_shader_delete (sat_opengl_program_t *object);
sat_status_t sat_opengl_program_delete (sat_opengl_program_t *object);
sat_status_t sat_opengl_program_enable (sat_opengl_program_t *object);

#endif/* SAT_OPENGL_PROGRAM_H_ */
