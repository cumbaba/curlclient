cmake_minimum_required(VERSION 2.8)

# include headerfiles for library
include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

add_library( defia.curlclient.lib
    CurlClient.cpp
    HttpRequestType.hpp
)

target_link_libraries ( defia.curlclient.lib
    curl
    ssl
    curlpp
    jsoncpp
)
