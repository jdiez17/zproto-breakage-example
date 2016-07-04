/*  =========================================================================
    aggregator_msg - System Aggregator Protocol

    Codec class for aggregator_msg.

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

/*
@header
    aggregator_msg - System Aggregator Protocol
@discuss
@end
*/

#include "../include/aggregator_msg.h"

//  Structure of our class

struct _aggregator_msg_t {
    zframe_t *routing_id;               //  Routing_id from ROUTER, if any
    int id;                             //  aggregator_msg message ID
    byte *needle;                       //  Read/write pointer for serialization
    byte *ceiling;                      //  Valid upper limit for read pointer
    char component [256];               //  Component name
    zlist_t *variables;                 //  List of variables that this component exposes, where each variable is a string such that the name of the variable is followed by a comma and the variable mode, which can be 'R' or 'RW'. For example, "temp1,RW".
    zlist_t *methods;                   //  List of methods that this component exposes
};

//  --------------------------------------------------------------------------
//  Network data encoding macros

//  Put a block of octets to the frame
#define PUT_OCTETS(host,size) { \
    memcpy (self->needle, (host), size); \
    self->needle += size; \
}

//  Get a block of octets from the frame
#define GET_OCTETS(host,size) { \
    if (self->needle + size > self->ceiling) { \
        zsys_warning ("aggregator_msg: GET_OCTETS failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, size); \
    self->needle += size; \
}

//  Put a 1-byte number to the frame
#define PUT_NUMBER1(host) { \
    *(byte *) self->needle = (byte) (host); \
    self->needle++; \
}

//  Put a 2-byte number to the frame
#define PUT_NUMBER2(host) { \
    self->needle [0] = (byte) (((host) >> 8)  & 255); \
    self->needle [1] = (byte) (((host))       & 255); \
    self->needle += 2; \
}

//  Put a 4-byte number to the frame
#define PUT_NUMBER4(host) { \
    self->needle [0] = (byte) (((host) >> 24) & 255); \
    self->needle [1] = (byte) (((host) >> 16) & 255); \
    self->needle [2] = (byte) (((host) >> 8)  & 255); \
    self->needle [3] = (byte) (((host))       & 255); \
    self->needle += 4; \
}

//  Put a 8-byte number to the frame
#define PUT_NUMBER8(host) { \
    self->needle [0] = (byte) (((host) >> 56) & 255); \
    self->needle [1] = (byte) (((host) >> 48) & 255); \
    self->needle [2] = (byte) (((host) >> 40) & 255); \
    self->needle [3] = (byte) (((host) >> 32) & 255); \
    self->needle [4] = (byte) (((host) >> 24) & 255); \
    self->needle [5] = (byte) (((host) >> 16) & 255); \
    self->needle [6] = (byte) (((host) >> 8)  & 255); \
    self->needle [7] = (byte) (((host))       & 255); \
    self->needle += 8; \
}

//  Get a 1-byte number from the frame
#define GET_NUMBER1(host) { \
    if (self->needle + 1 > self->ceiling) { \
        zsys_warning ("aggregator_msg: GET_NUMBER1 failed"); \
        goto malformed; \
    } \
    (host) = *(byte *) self->needle; \
    self->needle++; \
}

//  Get a 2-byte number from the frame
#define GET_NUMBER2(host) { \
    if (self->needle + 2 > self->ceiling) { \
        zsys_warning ("aggregator_msg: GET_NUMBER2 failed"); \
        goto malformed; \
    } \
    (host) = ((uint16_t) (self->needle [0]) << 8) \
           +  (uint16_t) (self->needle [1]); \
    self->needle += 2; \
}

//  Get a 4-byte number from the frame
#define GET_NUMBER4(host) { \
    if (self->needle + 4 > self->ceiling) { \
        zsys_warning ("aggregator_msg: GET_NUMBER4 failed"); \
        goto malformed; \
    } \
    (host) = ((uint32_t) (self->needle [0]) << 24) \
           + ((uint32_t) (self->needle [1]) << 16) \
           + ((uint32_t) (self->needle [2]) << 8) \
           +  (uint32_t) (self->needle [3]); \
    self->needle += 4; \
}

//  Get a 8-byte number from the frame
#define GET_NUMBER8(host) { \
    if (self->needle + 8 > self->ceiling) { \
        zsys_warning ("aggregator_msg: GET_NUMBER8 failed"); \
        goto malformed; \
    } \
    (host) = ((uint64_t) (self->needle [0]) << 56) \
           + ((uint64_t) (self->needle [1]) << 48) \
           + ((uint64_t) (self->needle [2]) << 40) \
           + ((uint64_t) (self->needle [3]) << 32) \
           + ((uint64_t) (self->needle [4]) << 24) \
           + ((uint64_t) (self->needle [5]) << 16) \
           + ((uint64_t) (self->needle [6]) << 8) \
           +  (uint64_t) (self->needle [7]); \
    self->needle += 8; \
}

//  Put a string to the frame
#define PUT_STRING(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER1 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a string from the frame
#define GET_STRING(host) { \
    size_t string_size; \
    GET_NUMBER1 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("aggregator_msg: GET_STRING failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}

//  Put a long string to the frame
#define PUT_LONGSTR(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER4 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a long string from the frame
#define GET_LONGSTR(host) { \
    size_t string_size; \
    GET_NUMBER4 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("aggregator_msg: GET_LONGSTR failed"); \
        goto malformed; \
    } \
    free ((host)); \
    (host) = (char *) malloc (string_size + 1); \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}


//  --------------------------------------------------------------------------
//  Create a new aggregator_msg

aggregator_msg_t *
aggregator_msg_new (void)
{
    aggregator_msg_t *self = (aggregator_msg_t *) zmalloc (sizeof (aggregator_msg_t));
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the aggregator_msg

void
aggregator_msg_destroy (aggregator_msg_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        aggregator_msg_t *self = *self_p;

        //  Free class properties
        zframe_destroy (&self->routing_id);
        if (self->variables)
            zlist_destroy (&self->variables);
        if (self->methods)
            zlist_destroy (&self->methods);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Receive a aggregator_msg from the socket. Returns 0 if OK, -1 if
//  there was an error. Blocks if there is no message waiting.

int
aggregator_msg_recv (aggregator_msg_t *self, zsock_t *input)
{
    assert (input);

    if (zsock_type (input) == ZMQ_ROUTER) {
        zframe_destroy (&self->routing_id);
        self->routing_id = zframe_recv (input);
        if (!self->routing_id || !zsock_rcvmore (input)) {
            zsys_warning ("aggregator_msg: no routing ID");
            return -1;          //  Interrupted or malformed
        }
    }
    zmq_msg_t frame;
    zmq_msg_init (&frame);
    int size = zmq_msg_recv (&frame, zsock_resolve (input), 0);
    if (size == -1) {
        zsys_warning ("aggregator_msg: interrupted");
        goto malformed;         //  Interrupted
    }
    //  Get and check protocol signature
    self->needle = (byte *) zmq_msg_data (&frame);
    self->ceiling = self->needle + zmq_msg_size (&frame);

    uint16_t signature;
    GET_NUMBER2 (signature);
    if (signature != (0xAAA0 | 1)) {
        zsys_warning ("aggregator_msg: invalid signature");
        //  TODO: discard invalid messages and loop, and return
        //  -1 only on interrupt
        goto malformed;         //  Interrupted
    }
    //  Get message id and parse per message type
    GET_NUMBER1 (self->id);

    switch (self->id) {
        case AGGREGATOR_MSG_COMPONENT_REGISTER:
            GET_STRING (self->component);
            {
                size_t list_size;
                GET_NUMBER4 (list_size);
                self->variables = zlist_new ();
                zlist_autofree (self->variables);
                while (list_size--) {
                    char *string = NULL;
                    GET_LONGSTR (string);
                    zlist_append (self->variables, string);
                    free (string);
                }
            }
            {
                size_t list_size;
                GET_NUMBER4 (list_size);
                self->methods = zlist_new ();
                zlist_autofree (self->methods);
                while (list_size--) {
                    char *string = NULL;
                    GET_LONGSTR (string);
                    zlist_append (self->methods, string);
                    free (string);
                }
            }
            break;

        case AGGREGATOR_MSG_COMPONENT_REGISTER_OK:
            break;

        default:
            zsys_warning ("aggregator_msg: bad message ID");
            goto malformed;
    }
    //  Successful return
    zmq_msg_close (&frame);
    return 0;

    //  Error returns
    malformed:
        zsys_warning ("aggregator_msg: aggregator_msg malformed message, fail");
        zmq_msg_close (&frame);
        return -1;              //  Invalid message
}


//  --------------------------------------------------------------------------
//  Send the aggregator_msg to the socket. Does not destroy it. Returns 0 if
//  OK, else -1.

int
aggregator_msg_send (aggregator_msg_t *self, zsock_t *output)
{
    assert (self);
    assert (output);

    if (zsock_type (output) == ZMQ_ROUTER)
        zframe_send (&self->routing_id, output, ZFRAME_MORE + ZFRAME_REUSE);

    size_t frame_size = 2 + 1;          //  Signature and message ID
    switch (self->id) {
        case AGGREGATOR_MSG_COMPONENT_REGISTER:
            frame_size += 1 + strlen (self->component);
            frame_size += 4;            //  Size is 4 octets
            if (self->variables) {
                char *variables = (char *) zlist_first (self->variables);
                while (variables) {
                    frame_size += 4 + strlen (variables);
                    variables = (char *) zlist_next (self->variables);
                }
            }
            frame_size += 4;            //  Size is 4 octets
            if (self->methods) {
                char *methods = (char *) zlist_first (self->methods);
                while (methods) {
                    frame_size += 4 + strlen (methods);
                    methods = (char *) zlist_next (self->methods);
                }
            }
            break;
    }
    //  Now serialize message into the frame
    zmq_msg_t frame;
    zmq_msg_init_size (&frame, frame_size);
    self->needle = (byte *) zmq_msg_data (&frame);
    PUT_NUMBER2 (0xAAA0 | 1);
    PUT_NUMBER1 (self->id);
    size_t nbr_frames = 1;              //  Total number of frames to send

    switch (self->id) {
        case AGGREGATOR_MSG_COMPONENT_REGISTER:
            PUT_STRING (self->component);
            if (self->variables) {
                PUT_NUMBER4 (zlist_size (self->variables));
                char *variables = (char *) zlist_first (self->variables);
                while (variables) {
                    PUT_LONGSTR (variables);
                    variables = (char *) zlist_next (self->variables);
                }
            }
            else
                PUT_NUMBER4 (0);    //  Empty string array
            if (self->methods) {
                PUT_NUMBER4 (zlist_size (self->methods));
                char *methods = (char *) zlist_first (self->methods);
                while (methods) {
                    PUT_LONGSTR (methods);
                    methods = (char *) zlist_next (self->methods);
                }
            }
            else
                PUT_NUMBER4 (0);    //  Empty string array
            break;

    }
    //  Now send the data frame
    zmq_msg_send (&frame, zsock_resolve (output), --nbr_frames? ZMQ_SNDMORE: 0);

    return 0;
}


//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
aggregator_msg_print (aggregator_msg_t *self)
{
    assert (self);
    switch (self->id) {
        case AGGREGATOR_MSG_COMPONENT_REGISTER:
            zsys_debug ("AGGREGATOR_MSG_COMPONENT_REGISTER:");
            zsys_debug ("    component='%s'", self->component);
            zsys_debug ("    variables=");
            if (self->variables) {
                char *variables = (char *) zlist_first (self->variables);
                while (variables) {
                    zsys_debug ("        '%s'", variables);
                    variables = (char *) zlist_next (self->variables);
                }
            }
            zsys_debug ("    methods=");
            if (self->methods) {
                char *methods = (char *) zlist_first (self->methods);
                while (methods) {
                    zsys_debug ("        '%s'", methods);
                    methods = (char *) zlist_next (self->methods);
                }
            }
            break;

        case AGGREGATOR_MSG_COMPONENT_REGISTER_OK:
            zsys_debug ("AGGREGATOR_MSG_COMPONENT_REGISTER_OK:");
            break;

    }
}


//  --------------------------------------------------------------------------
//  Get/set the message routing_id

zframe_t *
aggregator_msg_routing_id (aggregator_msg_t *self)
{
    assert (self);
    return self->routing_id;
}

void
aggregator_msg_set_routing_id (aggregator_msg_t *self, zframe_t *routing_id)
{
    if (self->routing_id)
        zframe_destroy (&self->routing_id);
    self->routing_id = zframe_dup (routing_id);
}


//  --------------------------------------------------------------------------
//  Get/set the aggregator_msg id

int
aggregator_msg_id (aggregator_msg_t *self)
{
    assert (self);
    return self->id;
}

void
aggregator_msg_set_id (aggregator_msg_t *self, int id)
{
    self->id = id;
}

//  --------------------------------------------------------------------------
//  Return a printable command string

const char *
aggregator_msg_command (aggregator_msg_t *self)
{
    assert (self);
    switch (self->id) {
        case AGGREGATOR_MSG_COMPONENT_REGISTER:
            return ("COMPONENT_REGISTER");
            break;
        case AGGREGATOR_MSG_COMPONENT_REGISTER_OK:
            return ("COMPONENT_REGISTER_OK");
            break;
    }
    return "?";
}

//  --------------------------------------------------------------------------
//  Get/set the component field

const char *
aggregator_msg_component (aggregator_msg_t *self)
{
    assert (self);
    return self->component;
}

void
aggregator_msg_set_component (aggregator_msg_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->component)
        return;
    strncpy (self->component, value, 255);
    self->component [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get the variables field, without transferring ownership

zlist_t *
aggregator_msg_variables (aggregator_msg_t *self)
{
    assert (self);
    return self->variables;
}

//  Get the variables field and transfer ownership to caller

zlist_t *
aggregator_msg_get_variables (aggregator_msg_t *self)
{
    assert (self);
    zlist_t *variables = self->variables;
    self->variables = NULL;
    return variables;
}

//  Set the variables field, transferring ownership from caller

void
aggregator_msg_set_variables (aggregator_msg_t *self, zlist_t **variables_p)
{
    assert (self);
    assert (variables_p);
    zlist_destroy (&self->variables);
    self->variables = *variables_p;
    *variables_p = NULL;
}



//  --------------------------------------------------------------------------
//  Get the methods field, without transferring ownership

zlist_t *
aggregator_msg_methods (aggregator_msg_t *self)
{
    assert (self);
    return self->methods;
}

//  Get the methods field and transfer ownership to caller

zlist_t *
aggregator_msg_get_methods (aggregator_msg_t *self)
{
    assert (self);
    zlist_t *methods = self->methods;
    self->methods = NULL;
    return methods;
}

//  Set the methods field, transferring ownership from caller

void
aggregator_msg_set_methods (aggregator_msg_t *self, zlist_t **methods_p)
{
    assert (self);
    assert (methods_p);
    zlist_destroy (&self->methods);
    self->methods = *methods_p;
    *methods_p = NULL;
}




//  --------------------------------------------------------------------------
//  Selftest

void
aggregator_msg_test (bool verbose)
{
    printf (" * aggregator_msg: ");

    if (verbose)
        printf ("\n");

    //  @selftest
    //  Simple create/destroy test
    aggregator_msg_t *self = aggregator_msg_new ();
    assert (self);
    aggregator_msg_destroy (&self);
    //  Create pair of sockets we can send through
    //  We must bind before connect if we wish to remain compatible with ZeroMQ < v4
    zsock_t *output = zsock_new (ZMQ_DEALER);
    assert (output);
    int rc = zsock_bind (output, "inproc://selftest-aggregator_msg");
    assert (rc == 0);

    zsock_t *input = zsock_new (ZMQ_ROUTER);
    assert (input);
    rc = zsock_connect (input, "inproc://selftest-aggregator_msg");
    assert (rc == 0);


    //  Encode/send/decode and verify each message type
    int instance;
    self = aggregator_msg_new ();
    aggregator_msg_set_id (self, AGGREGATOR_MSG_COMPONENT_REGISTER);

    aggregator_msg_set_component (self, "Life is short but Now lasts for ever");
    zlist_t *component_register_variables = zlist_new ();
    zlist_append (component_register_variables, "Name: Brutus");
    zlist_append (component_register_variables, "Age: 43");
    aggregator_msg_set_variables (self, &component_register_variables);
    zlist_t *component_register_methods = zlist_new ();
    zlist_append (component_register_methods, "Name: Brutus");
    zlist_append (component_register_methods, "Age: 43");
    aggregator_msg_set_methods (self, &component_register_methods);
    //  Send twice
    aggregator_msg_send (self, output);
    aggregator_msg_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        aggregator_msg_recv (self, input);
        assert (aggregator_msg_routing_id (self));
        assert (streq (aggregator_msg_component (self), "Life is short but Now lasts for ever"));
        zlist_t *variables = aggregator_msg_get_variables (self);
        assert (variables);
        assert (zlist_size (variables) == 2);
        assert (streq ((char *) zlist_first (variables), "Name: Brutus"));
        assert (streq ((char *) zlist_next (variables), "Age: 43"));
        zlist_destroy (&variables);
        zlist_destroy (&component_register_variables);
        zlist_t *methods = aggregator_msg_get_methods (self);
        assert (methods);
        assert (zlist_size (methods) == 2);
        assert (streq ((char *) zlist_first (methods), "Name: Brutus"));
        assert (streq ((char *) zlist_next (methods), "Age: 43"));
        zlist_destroy (&methods);
        zlist_destroy (&component_register_methods);
    }
    aggregator_msg_set_id (self, AGGREGATOR_MSG_COMPONENT_REGISTER_OK);

    //  Send twice
    aggregator_msg_send (self, output);
    aggregator_msg_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        aggregator_msg_recv (self, input);
        assert (aggregator_msg_routing_id (self));
    }

    aggregator_msg_destroy (&self);
    zsock_destroy (&input);
    zsock_destroy (&output);
    //  @end

    printf ("OK\n");
}
