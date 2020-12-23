#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <dbus/dbus.h>

static int running = 1;
static const char* pong = "pong";

/*
 * On SIGINT, exit the main loop
 */
static void sig_handler(int signo)
{
    if (signo == SIGINT) {
        running = 0;
    }
}

int main(int argc, char** argv)
{
    DBusConnection* conn = NULL;
    DBusError       err;
    
    // Set up the SIGINT signal handler
    if (signal(SIGINT, &sig_handler) == SIG_ERR) {
        fprintf(stderr, "Failed to register SIGINT handler\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialise the errors
    dbus_error_init(&err);
    
    // Connect to the bus and check for errors
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn || dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection error: %s\n", err.message);
        goto error;
    }
    
    // Request our name on the bus and check for errors
    int ret = dbus_bus_request_name(conn, "template.server.method",
                                    DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Request name error: %s\n", err.message);
        goto error;
    }
    
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
        fprintf(stderr, "*** Not primary owner: %d ***\n", ret);
        goto error;
    }
    
    // Main loop
    printf("Server running...\n");
    while (running) {
        // Non blocking read of the next available message
        dbus_connection_read_write(conn, 0);
        DBusMessage* msg = dbus_connection_pop_message(conn);
        if (!msg) {
            sleep(1);
            continue;
        }
        
        const char* interface = dbus_message_get_interface(msg);
        const char* member = dbus_message_get_member(msg);
        printf("Got message: interface='%s', member='%s'\n",
               interface, member);
               
        // Check this is a method call for the right interface & method
        if (dbus_message_is_method_call(msg,
                                        "template.server.Interface" /*iface*/,
                                        "Ping" /*method*/)) {
            DBusMessage* reply = dbus_message_new_method_return(msg);
            if (reply) {
                dbus_message_append_args(reply,
                                         DBUS_TYPE_STRING, &pong,
                                         DBUS_TYPE_INVALID);
                // Send the reply
                if (!dbus_connection_send(conn, reply, NULL)) {
                    fprintf(stderr, "Failed to send \"pong\" reply\n");
                } else {
                    // Block until write finishes
                    dbus_connection_flush(conn);
                }
                // Free the remply
                dbus_message_unref(reply);
            }
        }
        // Free the message
        dbus_message_unref(msg);
    }
    
    printf("Server exiting...\n");
    dbus_error_free(&err);
    return EXIT_SUCCESS;
    
error:
    dbus_error_free(&err);
    return EXIT_FAILURE;
}
