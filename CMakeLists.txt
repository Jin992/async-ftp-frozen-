cmake_minimum_required(VERSION 3.13)
project(asio_async_ftp)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)
find_package(Boost 1.67 COMPONENTS system regex filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(asio_async_ftp main.cpp AbstractClasses/AbstractAcceptor.cpp AbstractClasses/AbstractAcceptor.h AbstractClasses/AbstractConnection.cpp AbstractClasses/AbstractConnection.h Connection.cpp Connection.h)
target_link_libraries(asio_async_ftp ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})