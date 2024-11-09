#include <sat_opengl.h>
#include <sat_opengl_window.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>

struct sat_opengl_t 
{
    sat_opengl_window_t window;
    bool initialized;
};

static sat_status_t sat_opengl_check_args (sat_opengl_args_t *args);
static sat_status_t sat_opengl_init (void);

sat_status_t sat_opengl_create (sat_opengl_t **object, sat_opengl_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl create error");

    do 
    {
        if (object == NULL)
        {
            break;
        }

        status = sat_opengl_check_args (args);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = sat_opengl_init ();
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        sat_opengl_t *opengl = calloc (1, sizeof (struct sat_opengl_t));
        if (opengl == NULL)
        {
            break;
        }

        status = sat_opengl_window_create (&opengl->window, &(sat_opengl_window_args_t)
                                                            {
                                                                .height = args->window.height,
                                                                .width = args->window.width,
                                                                .title = args->window.title
                                                            });
        if (sat_status_get_result (&status) == false)
        {
            free (opengl);
            break;
        }

        opengl->initialized = true;
        *object = opengl;

    } while (false);

    return status;
}

sat_status_t sat_opengl_run (sat_opengl_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl run error");

    if (object != NULL && object->initialized == true)
    {
        sat_opengl_window_run (&object->window);

        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t sat_opengl_close (sat_opengl_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl close error");

    if (object != NULL && object->initialized == true)
    {
        sat_opengl_window_close (&object->window);

        glfwTerminate ();

        sat_status_set (&status, true, "");
    }

    return status;
}


static sat_status_t sat_opengl_check_args (sat_opengl_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl check args error");

    if (args->window.height > 0 &&
        args->window.width > 0 &&
        args->window.title != NULL && 
        strlen (args->window.title) > 0)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}

static sat_status_t sat_opengl_init (void)
{
    sat_status_t status = sat_status_set (&status, false, "sat opengl init error");

    if (glfwInit () == GL_TRUE &&
        glewInit () == GL_TRUE)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}