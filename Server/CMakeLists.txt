# File dependency
file(GLOB HEADERS "./core/*.hpp")
file(GLOB SOURCES "./core/*.cpp")

# Project source files
add_executable(babel_server ${HEADERS} ${SOURCES})

if(UNIX)
    target_compile_options(babel_server PRIVATE -Wall -Wextra -Werror -Wpedantic -g)

    # Project library linking flag
    target_link_libraries(
        babel_server
        -lstdc++
        -lpthread
        -lboost_serialization
        -lboost_system
        -lboost_system
        -lboost_thread
        -pthread
    )
endif(UNIX)


if(WIN32)
    target_compile_options(babel_server PRIVATE -Wall -Wextra -Werror -Wpedantic -g -lws_32)

    # Project library linking flag
    target_link_libraries(
        babel_server
        -lstdc++
        -lpthread
        -pthread
        -lboost_serialization-mt
        -lboost_system-mt
        -lboost_chrono-mt
        ws2_32
        wsock32
    )
endif(WIN32)

# Project dependencies
target_include_directories(
    babel_server PRIVATE 
    ./include/
    ./source/components/
    ./source/system/
    ./source/entity/
    ${CMAKE_SOURCE_DIR}/Engine/
)
