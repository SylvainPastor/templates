#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <dbus/dbus.h>

static const char* pong = "pong";

int main(int argc, char** argv)
{
    DBusConnection*  conn    = NULL;
    DBusMessage*     msg     = NULL;
    DBusPendingCall* pending = NULL;
    DBusError        err;
    
    int res = EXIT_FAILURE;
    
    // Initialise the errors
    dbus_error_init(&err);
    
    // Connect to the bus and check for errors
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn || dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection error: %s\n", err.message);
        goto end;
    }
    
    // Request our name on the bus and check for errors
    int ret = dbus_bus_request_name(conn, "template.client.method",
                                    DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Request name error: %s\n", err.message);
        goto end;
    }
    
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
        fprintf(stderr, "*** Not primary owner: %d ***\n", ret);
        goto end;
    }
    
    // Create a new method call and check for errors
    msg = dbus_message_new_method_call("template.server.method",    // target for the method call
                                       "/template/server/method",   // object to call on
                                       "template.server.Interface", // interface to call on
                                       "Ping");                     // method name
    if (msg) {
        // Send message and get a handle for a reply
        if (!dbus_connection_send_with_reply(conn, msg,
                                             &pending,
                                             -1 /*Infinite timeout*/)) {
            goto end;
        }
        
        // Test pending call
        if (!pending) {
            fprintf(stderr, "No pending call\n");
            goto end;
        }
        
        // Block until write finishes
        dbus_connection_flush(conn);
        
        printf("> Ping request sent\n");
        
        // Free message
        dbus_message_unref(msg);
        
        // Block until we recieve a reply
        dbus_pending_call_block(pending);
        
        // Get the reply message
        msg = dbus_pending_call_steal_reply(pending);
        if (msg) {
            const char* reply;
            if (dbus_message_get_args(msg, &err,
                                      DBUS_TYPE_STRING, &reply,
                                      DBUS_TYPE_INVALID)) {
                if (strcmp(pong, reply) == 0) {
                    res = EXIT_SUCCESS;
                    printf("< %s reply received\n", reply);
                } else {
                    fprintf(stderr, "Invalid reply received: %s\n", reply);
                }
            }
            // Free reply message
            dbus_message_unref(msg);
        }
        // Free the pending message handle
        dbus_pending_call_unref(pending);
    } else {
        fprintf(stderr, "Failed to create message: No memory\n");
    }
    
end:
    dbus_error_free(&err);
    return res;
}
