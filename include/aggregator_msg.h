/*  =========================================================================
    aggregator_msg - System Aggregator Protocol

    Codec header for aggregator_msg.

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: aggregator_msg.xml, or
     * The code generation script that built this file: zproto_codec_c
    ************************************************************************
    =========================================================================
*/

#ifndef AGGREGATOR_MSG_H_INCLUDED
#define AGGREGATOR_MSG_H_INCLUDED

/*  These are the aggregator_msg messages:

    COMPONENT_REGISTER - Component signals to the aggregator that it is ready.
        component           string      Component name
        variables           strings     List of variables that this component exposes, where each variable is a string such that the name of the variable is followed by a comma and the variable mode, which can be 'R' or 'RW'. For example, "temp1,RW".
        methods             strings     List of methods that this component exposes

    COMPONENT_REGISTER_OK - Aggregator signals to the component that it has been registered successfully.
*/

#define AGGREGATOR_MSG_VERSION              1

#define AGGREGATOR_MSG_COMPONENT_REGISTER   1
#define AGGREGATOR_MSG_COMPONENT_REGISTER_OK  2

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
#ifndef AGGREGATOR_MSG_T_DEFINED
typedef struct _aggregator_msg_t aggregator_msg_t;
#define AGGREGATOR_MSG_T_DEFINED
#endif

//  @interface
//  Create a new empty aggregator_msg
aggregator_msg_t *
    aggregator_msg_new (void);

//  Destroy a aggregator_msg instance
void
    aggregator_msg_destroy (aggregator_msg_t **self_p);

//  Receive a aggregator_msg from the socket. Returns 0 if OK, -1 if
//  there was an error. Blocks if there is no message waiting.
int
    aggregator_msg_recv (aggregator_msg_t *self, zsock_t *input);

//  Send the aggregator_msg to the output socket, does not destroy it
int
    aggregator_msg_send (aggregator_msg_t *self, zsock_t *output);


//  Print contents of message to stdout
void
    aggregator_msg_print (aggregator_msg_t *self);

//  Get/set the message routing id
zframe_t *
    aggregator_msg_routing_id (aggregator_msg_t *self);
void
    aggregator_msg_set_routing_id (aggregator_msg_t *self, zframe_t *routing_id);

//  Get the aggregator_msg id and printable command
int
    aggregator_msg_id (aggregator_msg_t *self);
void
    aggregator_msg_set_id (aggregator_msg_t *self, int id);
const char *
    aggregator_msg_command (aggregator_msg_t *self);

//  Get/set the component field
const char *
    aggregator_msg_component (aggregator_msg_t *self);
void
    aggregator_msg_set_component (aggregator_msg_t *self, const char *value);

//  Get/set the variables field
zlist_t *
    aggregator_msg_variables (aggregator_msg_t *self);
//  Get the variables field and transfer ownership to caller
zlist_t *
    aggregator_msg_get_variables (aggregator_msg_t *self);
//  Set the variables field, transferring ownership from caller
void
    aggregator_msg_set_variables (aggregator_msg_t *self, zlist_t **variables_p);

//  Get/set the methods field
zlist_t *
    aggregator_msg_methods (aggregator_msg_t *self);
//  Get the methods field and transfer ownership to caller
zlist_t *
    aggregator_msg_get_methods (aggregator_msg_t *self);
//  Set the methods field, transferring ownership from caller
void
    aggregator_msg_set_methods (aggregator_msg_t *self, zlist_t **methods_p);

//  Self test of this class
void
    aggregator_msg_test (bool verbose);
//  @end

//  For backwards compatibility with old codecs
#define aggregator_msg_dump  aggregator_msg_print

#ifdef __cplusplus
}
#endif

#endif
