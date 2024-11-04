#include <sat_tcp_server_abstract.h>
#include <sat_tcp_server_interactive.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

static sat_status_t sat_tcp_server_abstract_set_socket (sat_tcp_server_abstract_t *object);
static sat_status_t sat_tcp_server_abstract_set_reuse_address (sat_tcp_server_abstract_t *object);
static sat_status_t sat_tcp_server_abstract_set_bind (sat_tcp_server_abstract_t *object);
static sat_status_t sat_tcp_server_abstract_listen (sat_tcp_server_abstract_t *object);
static sat_status_t sat_tcp_server_abstract_select_type (sat_tcp_server_abstract_t *object);

void sat_tcp_server_abstract_copy_to_context (sat_tcp_server_abstract_t *object, sat_tcp_server_args_t *args)
{
    object->buffer = args->buffer;
    object->size = args->size;
    object->port = args->port;
    object->events.on_receive = args->events.on_receive;
    object->events.on_send = args->events.on_send;
    object->data = args->data;
    object->type = args->type;
}

sat_status_t sat_tcp_server_abstract_is_args_valid (sat_tcp_server_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server args error");

    if (args->buffer != NULL &&
        args->size > 0 && 
        args->port != NULL)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t sat_tcp_server_abstract_configure (sat_tcp_server_abstract_t *object)
{
    sat_status_t status;

    do 
    {
        status = sat_tcp_server_abstract_set_socket (object);
        if (sat_status_get_result (&status) == false)
            break;

        status = sat_tcp_server_abstract_set_reuse_address (object);
        if (sat_status_get_result (&status) == false)
            break;

        status = sat_tcp_server_abstract_set_bind (object);
        if (sat_status_get_result (&status) == false)
            break;

        status = sat_tcp_server_abstract_select_type (object);
        if (sat_status_get_result (&status) == false)
            break;

        status = sat_tcp_server_abstract_listen (object);

    } while (false);

    return status;
}

static sat_status_t sat_tcp_server_abstract_set_socket (sat_tcp_server_abstract_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server set socket error");

    object->socket = socket (AF_INET, SOCK_STREAM, 0);
    if (object->socket >= 0)
        sat_status_set (&status, true, "");

    return status;
}

static sat_status_t sat_tcp_server_abstract_set_reuse_address (sat_tcp_server_abstract_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server set reuse address error");
    int yes = 1;

    if (setsockopt (object->socket, SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof (yes)) == 0)
        sat_status_set (&status, true, "");

    return status;
}

static sat_status_t sat_tcp_server_abstract_set_bind (sat_tcp_server_abstract_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server set bind error");

    struct sockaddr_in address;

    memset (&address, 0, sizeof (struct sockaddr_in));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons (atoi (object->port));

    if (bind (object->socket, (const struct sockaddr *)&address, sizeof (struct sockaddr_in)) == 0)
        sat_status_set (&status, true, "");

    return status;
}

static sat_status_t sat_tcp_server_abstract_listen (sat_tcp_server_abstract_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server listen error");
    
    if (listen (object->socket, 1) >= 0)
        sat_status_set (&status, true, "");

    return status;
}

static sat_status_t sat_tcp_server_abstract_select_type (sat_tcp_server_abstract_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "sat tcp server select type error");
    
    if (object->type == sat_tcp_server_type_interactive)
    {

        object->base = sat_tcp_server_interactive_create ();

        sat_status_set (&status, true, "");
    }

    return status;
}