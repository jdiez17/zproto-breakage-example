/*  =========================================================================
    aggregator_broker - aggregator_broker

    =========================================================================
*/

/*
@header
    Description of class for man page.
@discuss
    Detailed discussion of the class, if any.
@end
*/

//  TODO: Change these to match your project's needs
#include "../include/aggregator_msg.h"
#include "../include/aggregator_broker.h"

//  ---------------------------------------------------------------------------
//  Forward declarations for the two main classes we use here

typedef struct _server_t server_t;
typedef struct _client_t client_t;

//  This structure defines the context for each running server. Store
//  whatever properties and structures you need for the server.

struct _server_t {
    //  These properties must always be present in the server_t
    //  and are set by the generated engine; do not modify them!
    zsock_t *pipe;              //  Actor pipe back to caller
    zconfig_t *config;          //  Current loaded configuration

    //  TODO: Add any properties you need here
};

//  ---------------------------------------------------------------------------
//  This structure defines the state for each client connection. It will
//  be passed to each action in the 'self' argument.

struct _client_t {
    //  These properties must always be present in the client_t
    //  and are set by the generated engine; do not modify them!
    server_t *server;           //  Reference to parent server
    aggregator_msg_t *message;  //  Message in and out

    //  TODO: Add specific properties for your application
};

//  Include the generated server engine
#include "aggregator_broker_engine.inc"

//  Allocate properties and structures for a new server instance.
//  Return 0 if OK, or -1 if there was an error.

static int
server_initialize (server_t *self)
{
    //  Construct properties here
    return 0;
}

//  Free properties and structures for a server instance

static void
server_terminate (server_t *self)
{
    //  Destroy properties here
}

//  Process server API method, return reply message if any

static zmsg_t *
server_method (server_t *self, const char *method, zmsg_t *msg)
{
    return NULL;
}


//  Allocate properties and structures for a new client connection and
//  optionally engine_set_next_event (). Return 0 if OK, or -1 on error.

static int
client_initialize (client_t *self)
{
    //  Construct properties here
    return 0;
}

//  Free properties and structures for a client connection

static void
client_terminate (client_t *self)
{
    //  Destroy properties here
}

//  ---------------------------------------------------------------------------
//  Selftest

void
aggregator_broker_test (bool verbose)
{
    printf (" * aggregator_broker: ");
    if (verbose)
        printf ("\n");

    //  @selftest
    zactor_t *server = zactor_new (aggregator_broker, "server");
    if (verbose)
        zstr_send (server, "VERBOSE");
    zstr_sendx (server, "BIND", "ipc://@/aggregator_broker", NULL);

    zsock_t *client = zsock_new (ZMQ_DEALER);
    assert (client);
    zsock_set_rcvtimeo (client, 2000);
    zsock_connect (client, "ipc://@/aggregator_broker");

    //  TODO: fill this out
    aggregator_msg_t *request = aggregator_msg_new ();
    aggregator_msg_destroy (&request);

    zsock_destroy (&client);
    zactor_destroy (&server);
    //  @end
    printf ("OK\n");
}


//  ---------------------------------------------------------------------------
//  handle_component_register
//

static void
handle_component_register (client_t *self)
{
    printf("Do the thing with the thing\n");
}


//  ---------------------------------------------------------------------------
//  handle_list_components
//

static void
handle_list_components (client_t *self)
{
    printf("Do the other thing with the other thing\n");
}


//  ---------------------------------------------------------------------------
//  handle_component_register
//

static void
handle_component_register (client_t *self)
{

}


//  ---------------------------------------------------------------------------
//  handle_list_components
//

static void
handle_list_components (client_t *self)
{

}
