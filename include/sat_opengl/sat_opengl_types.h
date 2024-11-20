#ifndef SAT_OPENGL_TYPES_H_
#define SAT_OPENGL_TYPES_H_

#include <stdint.h>

typedef enum 
{
    sat_opengl_shader_type_vertex,
    sat_opengl_shader_type_fragment,
    
} sat_opengl_shader_type_t;

typedef struct 
{
    float *list;
    uint32_t size;

} sat_opengl_vertices_t;

typedef struct 
{
    unsigned int *list;
    uint32_t size;

} sat_opengl_indexes_t;

typedef struct 
{
    int location;
    int amount;
    int elements;
    int offset;

} sat_opengl_attribute_t;

typedef struct 
{
    const char *name;
    sat_opengl_vertices_t vertices;
    sat_opengl_attribute_t attribute;
    sat_opengl_indexes_t indexes;

} sat_opengl_vbo_args_t;

typedef struct 
{
    float red;
    float green;
    float blue;
    float alpha;
    
} sat_opengl_color_t;

typedef enum 
{
    sat_opengl_draw_type_triangles,
    sat_opengl_draw_type_elements,
    
} sat_opengl_draw_type_t;

#endif/* SAT_OPENGL_TYPES_H_ */
