cmake_minimum_required(VERSION 2.8)

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

add_executable(curlclient_test "main.cpp")

target_link_libraries ( curlclient_test
    defia.curlclient.lib
)
