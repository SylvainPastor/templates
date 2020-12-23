# Low Level D-Bus C API templates

***libdbus*** is a low-level implementation that was never meant to be used directly by application developers, but as a reference guide for other reimplementations of D-Bus.

- [D-Bus Wikipedia Definition](https://en.wikipedia.org/wiki/D-Bus)
- [D-Bus Documentation](https://dbus.freedesktop.org/doc/api/html/index.html)

# How to build

```sh
$ ./build.sh 
-- The C compiler identification is GNU 7.5.0
-- The CXX compiler identification is GNU 7.5.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found PkgConfig: /usr/bin/pkg-config (found version "0.29.1") 
-- Found DBUS: /usr/include/dbus-1.0;/usr/lib/x86_64-linux-gnu/dbus-1.0/include  

-- Found dbus: /usr/include/dbus-1.0, /usr/lib/x86_64-linux-gnu/dbus-1.0/include
-- Found dbus: /usr/lib/x86_64-linux-gnu/libdbus-1.so

-- Configuring done
-- Generating done
-- Build files have been written to: /home/sylvain/work/templates/dbus/low-level/build
Scanning dependencies of target server
[ 25%] Building C object server/CMakeFiles/server.dir/server.c.o
[ 50%] Linking C executable server
[ 50%] Built target server
Scanning dependencies of target client
[ 75%] Building C object client/CMakeFiles/client.dir/client.c.o
[100%] Linking C executable client
[100%] Built target client
```
