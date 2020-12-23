cmake_minimum_required(VERSION 3.1)

project(DBusTemplate)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

# Try to find dbus library
find_package(dbus REQUIRED)

message("")
message("-- Found dbus: ${DBUS_INCLUDE_DIR}, ${DBUS_ARCH_INCLUDE_DIR}")
message("-- Found dbus: ${DBUS_LIBRARIES}")
message("")

# Add include directories
include_directories(
	${DBUS_INCLUDE_DIR}
	${DBUS_ARCH_INCLUDE_DIR}
)

# Template server
add_subdirectory(server)

# Template client
add_subdirectory(client)
