#include <sat_opengl_program.h>
#include <sat_iterator.h>
#include <GL/glew.h>

static sat_status_t sat_opengl_program_check_link_status (sat_opengl_shader_t *object);

sat_status_t sat_opengl_program_create (sat_opengl_program_t *object, sat_opengl_program_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl program create error");

    do 
    {
        object->id = glCreateProgram ();
        if (object->id == 0)
        {
            break;
        }

        status = sat_array_create (&object->shaders, &(sat_array_args_t)
                                                    {
                                                        .size = 1,
                                                        .object_size = sizeof (sat_opengl_shader_t),
                                                        .mode = sat_array_mode_dynamic,
                                                    });

        object->name = args->name;

    } while (false);

    return status;
}

sat_status_t sat_opengl_program_shader_add (sat_opengl_program_t *object, sat_opengl_shader_t *shader)
{
    return sat_array_add (object->shaders, (void *)shader);
}

sat_status_t sat_opengl_program_link (sat_opengl_program_t *object)
{
    sat_iterator_t iterator;
    sat_status_t status;
    uint32_t size;

    do 
    {
        status = sat_array_get_size (object->shaders, &size);
        if (size == 0)
        {
            break;
        }

        status = sat_iterator_open (&iterator, object->shaders);

        sat_opengl_shader_t *shader = (sat_opengl_shader_t *) sat_iterator_next (&iterator);

        while (shader != NULL)
        {
            glAttachShader (object->id, shader->id);
            shader = (sat_opengl_shader_t *) sat_iterator_next (&iterator);
        }

        glLinkProgram (object->id);

        status = sat_opengl_program_check_link_status (object);

        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = sat_opengl_program_shader_delete (object);

    } while (false);

    return status;
}

/* TODO make this function private */
sat_status_t sat_opengl_program_shader_delete (sat_opengl_program_t *object)
{
    sat_iterator_t iterator;
    sat_status_t status;
    uint32_t size;

    do 
    {
        status = sat_array_get_size (object->shaders, &size);
        if (size == 0)
        {
            break;
        }

        status = sat_iterator_open (&iterator, object->shaders);

        sat_opengl_shader_t *shader = (sat_opengl_shader_t *) sat_iterator_next (&iterator);

        while (shader != NULL)
        {
            sat_opengl_shader_free (shader);

            shader = (sat_opengl_shader_t *) sat_iterator_next (&iterator);
        }

    } while (false);

    return status;
}

sat_status_t sat_opengl_program_delete (sat_opengl_program_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl program delete error");

    if (glIsProgram (object->id) == GL_TRUE)
    {
        glDeleteProgram (object->id);

        status = sat_array_destroy (object->shaders);
    }

    return status;
}

sat_status_t sat_opengl_program_enable (sat_opengl_program_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl program enable error");

    if (glIsProgram (object->id) == GL_TRUE)
    {
        glUseProgram (object->id);

        sat_status_set (&status, true, "");
    }

    return status;
}

static sat_status_t sat_opengl_program_check_link_status (sat_opengl_shader_t *object)
{
    sat_status_t status = sat_status_set (&status, true, "");
    int success;

    glGetShaderiv (object->id, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        char info [512] = {0};

        glGetProgramInfoLog (object->id, sizeof (info), NULL, info);

        // log this error

        sat_status_set (&status, false, "sat opengl program link error");
    }

    return status;    
}