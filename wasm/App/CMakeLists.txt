cmake_minimum_required(VERSION 2.6)

#find_package(PkgConfig)

project(OpenSiv3D_Web CXX)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

add_custom_target(copy-data-files ALL COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
add_custom_target(copy-data-files2 ALL COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/resources/engine/font ${CMAKE_BINARY_DIR}/engine/font)


set(CMAKE_CXX_COMPILER "em++")
set(CMAKE_CXX_FLAGS "-std=c++17 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG -s USE_SDL=2 -msimd128 -s USE_FREETYPE=1 -s USE_LIBPNG=1 -s USE_FREETYPE=1 -s USE_HARFBUZZ=1 --preload-file assets --preload-file engine/font ")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

set(CMAKE_C_COMPILER "emcc")
#set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall -Wextra -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG -s USE_SDL=2  -msimd128 -s USE_FREETYPE=1 -s USE_LIBPNG=1 -s USE_FREETYPE=1 -s USE_HARFBUZZ=1 --preload-file assets --preload-file engine/font ")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

set(CMAKE_EXECUTABLE_SUFFIX ".html")

include_directories(
    "../../Siv3D/include"
    "../../Siv3D/include/ThirdParty"
)

set(SOURCE_FILES
    "./Main.cpp"
)


add_executable(Siv3D_Appx ${SOURCE_FILES})

target_link_libraries(Siv3D_Appx
    ${PROJECT_SOURCE_DIR}/../build/libSiv3D.a
)
