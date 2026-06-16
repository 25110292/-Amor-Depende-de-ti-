cmake_minimum_required(VERSION 3.10)
project(AmorDependeDeTi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 3 instalado via pacman en MSYS2/MinGW64
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/EventManager.cpp
)

set(HEADERS
    include/Game.h
    include/Player.h
    include/Event.h
    include/EventManager.h
)

add_executable(amor_depende_de_ti ${SOURCES} ${HEADERS})
target_include_directories(amor_depende_de_ti PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# SFML 3 usa namespace SFML::
target_link_libraries(amor_depende_de_ti PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# Copiar assets al lado del ejecutable
add_custom_command(TARGET amor_depende_de_ti POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:amor_depende_de_ti>/assets"
    COMMENT "Copiando assets..."
)

set_target_properties(amor_depende_de_ti PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
