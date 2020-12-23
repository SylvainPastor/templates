add_executable("server" server.c)

target_link_libraries("server" ${DBUS_LIBRARIES})
