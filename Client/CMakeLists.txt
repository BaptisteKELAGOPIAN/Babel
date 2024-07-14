set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# File dependency
file(GLOB HEADERS "./core/*.hpp")
file(GLOB SOURCES "./core/*.cpp")
file(GLOB SUBFOLDERS "./core/source/components/*.hpp" "./core/source/system/*.hpp" "./core/source/entity/*.hpp")

# Project source files
add_executable(babel_client ${SUBFOLDERS} ${HEADERS} ${SOURCES} ${MOC_SOURCES})

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Core Network REQUIRED)
# Project compilation flags

qt5_wrap_cpp(MOC_SOURCES udpclient.h)
# Project compilation flags
if(UNIX)
    target_compile_options(babel_client PRIVATE -Wall -Wextra -Werror -Wpedantic -g)
    target_link_libraries(
    babel_client
    -lstdc++
    -lpthread
    -lboost_serialization
    -lboost_system
    -lboost_system
    -lboost_thread
    -lopus
    -lportaudio
    Qt5::Core
    Qt5::Network
    Qt5::Widgets
    -pthread
)
endif(UNIX)

if(WIN32)
    target_compile_options(babel_client PRIVATE -Wall -Wextra -Werror -Wpedantic -g -lws_32)# -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 )
    target_link_libraries(
        babel_client
        -lstdc++
        -lpthread
        -pthread
        -lboost_serialization-mt
        -lboost_system-mt
        -lboost_chrono-mt
        -lopus
        -lportaudio
        Qt5::Core
        Qt5::Network
        Qt5::Widgets
        ws2_32
        wsock32
    )
endif(WIN32)

# Project dependencies
target_include_directories(
    babel_client PRIVATE
    ./include/
    ./source/components/
    ./source/system/
    ./source/entity/
    ./include/ ${CMAKE_SOURCE_DIR}/Engine/
)
