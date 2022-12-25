cmake_minimum_required(VERSION 3.0.0)
project(medici VERSION 0.1.0)

include(CTest)
enable_testing()

SET(CMAKE_CXX_STANDARD 20)

if(WIN32)
message("win")
elseif(APPLE)
message("apple")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework ApplicationServices")
elseif(UNIX)
if(${CMAKE_SYSTEM} MATCHES Linux)
message("linux")
endif()
else()
message("not supported")
endif()

set(SRC_FILES src/main.cpp)

set(SRC_DIRECTORY src/application/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}application.cpp
    ${SRC_DIRECTORY}argumenthandler.cpp
)

set(SRC_DIRECTORY src/configmanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}configmanager.cpp
)

set(SRC_DIRECTORY src/connectionmanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}connectionmanager.cpp
)

set(SRC_DIRECTORY src/data/)
list(
    APPEND SRC_FILES 
    ${SRC_DIRECTORY}config.cpp
    ${SRC_DIRECTORY}data.cpp
    ${SRC_DIRECTORY}display.cpp
    ${SRC_DIRECTORY}event.cpp
    ${SRC_DIRECTORY}jsondata.cpp
    ${SRC_DIRECTORY}keyboardevent.cpp
    ${SRC_DIRECTORY}mouseevent.cpp
    ${SRC_DIRECTORY}packet.cpp
    ${SRC_DIRECTORY}point.cpp
    ${SRC_DIRECTORY}rect.cpp
    ${SRC_DIRECTORY}uuid.cpp
)

set(SRC_DIRECTORY src/dependencyset/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}dependencyset.cpp
)

set(SRC_DIRECTORY src/displaymanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}displaymanager.cpp
    ${SRC_DIRECTORY}displaymanagerapple.cpp
    ${SRC_DIRECTORY}displaymanagerlinux.cpp
    ${SRC_DIRECTORY}displaymanagerwindows.cpp
)

set(SRC_DIRECTORY src/inputmanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}inputmanager.cpp
    ${SRC_DIRECTORY}inputmanagerapple.cpp
    ${SRC_DIRECTORY}inputmanagerlinux.cpp
    ${SRC_DIRECTORY}inputmanagerwindows.cpp
)

set(SRC_DIRECTORY src/platformmanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}platformmanager.cpp
)

set(SRC_DIRECTORY src/servermanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}servermanager.cpp
)

set(SRC_DIRECTORY src/statemanager/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}statemanager.cpp
)

set(SRC_DIRECTORY src/tcp/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}tcpclient.cpp
    ${SRC_DIRECTORY}tcpserver.cpp
    ${SRC_DIRECTORY}tcpsocket.cpp
)

set(SRC_DIRECTORY src/util/)
list(
    APPEND SRC_FILES
    ${SRC_DIRECTORY}log.cpp
    ${SRC_DIRECTORY}rectmagnetutil.cpp
    ${SRC_DIRECTORY}textutil.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
