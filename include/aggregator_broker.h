/*  =========================================================================
    aggregator_broker - System Aggregator Broker

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: aggregator_broker.xml, or
     * The code generation script that built this file: zproto_server_c
    ************************************************************************
    =========================================================================
*/

#ifndef AGGREGATOR_BROKER_H_INCLUDED
#define AGGREGATOR_BROKER_H_INCLUDED

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  To work with aggregator_broker, use the CZMQ zactor API:
//
//  Create new aggregator_broker instance, passing logging prefix:
//
//      zactor_t *aggregator_broker = zactor_new (aggregator_broker, "myname");
//
//  Destroy aggregator_broker instance
//
//      zactor_destroy (&aggregator_broker);
//
//  Enable verbose logging of commands and activity:
//
//      zstr_send (aggregator_broker, "VERBOSE");
//
//  Bind aggregator_broker to specified endpoint. TCP endpoints may specify
//  the port number as "*" to aquire an ephemeral port:
//
//      zstr_sendx (aggregator_broker, "BIND", endpoint, NULL);
//
//  Return assigned port number, specifically when BIND was done using an
//  an ephemeral port:
//
//      zstr_sendx (aggregator_broker, "PORT", NULL);
//      char *command, *port_str;
//      zstr_recvx (aggregator_broker, &command, &port_str, NULL);
//      assert (streq (command, "PORT"));
//
//  Specify configuration file to load, overwriting any previous loaded
//  configuration file or options:
//
//      zstr_sendx (aggregator_broker, "LOAD", filename, NULL);
//
//  Set configuration path value:
//
//      zstr_sendx (aggregator_broker, "SET", path, value, NULL);
//
//  Save configuration data to config file on disk:
//
//      zstr_sendx (aggregator_broker, "SAVE", filename, NULL);
//
//  Send zmsg_t instance to aggregator_broker:
//
//      zactor_send (aggregator_broker, &msg);
//
//  Receive zmsg_t instance from aggregator_broker:
//
//      zmsg_t *msg = zactor_recv (aggregator_broker);
//
//  This is the aggregator_broker constructor as a zactor_fn:
//
void
    aggregator_broker (zsock_t *pipe, void *args);

//  Self test of this class
void
    aggregator_broker_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
