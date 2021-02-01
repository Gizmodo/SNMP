cmake_minimum_required(VERSION 3.10)
project(snmp)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 17)
include_directories(
        /usr/local/include/mongocxx/v_noabi
        /usr/local/include/bsoncxx/v_noabi
        /usr/local/include/libbson-1.0
        /usr/local/include/libmongoc-1.0
        /home/user/Downloads/mongo-cxx-driver-r3.6.2/src
        /usr/local/include/net-snmp
        /home/user/Downloads/net-snmp-5.9/include/net-snmp
)

set(Boost_USE_STATIC OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS thread log log_setup system  date_time  chrono REQUIRED)
find_package(rxcpp CONFIG)

if (Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    #    include_directories(${Boost_INCLUDE_DIRS})

endif ()

project(NEW)
add_executable(NEW main.cpp)
set_target_properties(NEW PROPERTIES OUTPUT_NAME "NEW")
target_link_libraries(NEW
        /usr/local/lib/libbson-1.0.so
        /usr/local/lib/libmongoc-1.0.so
       # /usr/local/lib/libbsoncxx.so.3.4.0
        #/usr/local/lib/libbsoncxx.so._noabi
        #/usr/local/lib/libmongocxx.so._noabi
        #/home/user/boost_1_70_0/stage/lib/libboost_system.a
        #/home/user/boost_1_70_0/stage/lib/libboost_thread.a
        #/home/user/boost_1_70_0/stage/lib/libboost_log.a
        /usr/local/lib/libnetsnmp.so
        )

project(snmp_mongo)
add_executable(snmp_mongo snmp_mongo.cpp)
set_target_properties(snmp_mongo PROPERTIES OUTPUT_NAME "snmp_mongo")
target_link_libraries(snmp_mongo
        #/usr/local/lib/libbsoncxx.so.3.4.0
        /usr/local/lib/libbsoncxx.so._noabi
        /usr/local/lib/libmongocxx.so._noabi
        /usr/local/lib/libboost_system.a
        /usr/local/lib/libboost_thread.a
        /usr/local/lib/libboost_log.a
        /usr/local/lib/libnetsnmp.so
        )

project(asyncapp)
add_executable(asyncapp asyncapp.cpp)
set_target_properties(asyncapp PROPERTIES OUTPUT_NAME "asyncapp")
target_link_libraries(asyncapp
        /usr/local/lib/libboost_system.a
        /usr/local/lib/libboost_thread.a
        /usr/local/lib/libboost_log.a
        /usr/local/lib/libnetsnmp.so
        )

project(snmpmanager)
add_executable(snmpanager SnmpManager/mainSnmpManager.cpp SnmpManager/Manager.cpp SnmpManager/Manager.h SnmpManager/Host.h)
set_target_properties(snmpanager PROPERTIES OUTPUT_NAME "snmpanager")
target_link_libraries(snmpanager
        /usr/local/lib/libnetsnmp.so
        )