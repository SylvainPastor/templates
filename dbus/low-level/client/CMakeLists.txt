add_executable("client" client.c)

target_link_libraries("client" ${DBUS_LIBRARIES})
