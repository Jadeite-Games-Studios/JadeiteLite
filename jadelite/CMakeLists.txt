include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# get ImGui, no build needed (only the files) 
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        docking
  GIT_SHALLOW 1
)

FetchContent_MakeAvailable(imgui)
 
file(
	GLOB IM_SOURCES
	${imgui_SOURCE_DIR}/*.cpp
	# .cpp files for backends
	${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IM_SOURCES} )

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
    glad::glad
)

# Gather all sources from all folders 
file(GLOB_RECURSE CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB_RECURSE LOGGER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/logger/*.cpp)
file(GLOB_RECURSE GUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/*.cpp)
file(GLOB_RECURSE PLATFORM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/*.cpp)
file(GLOB_RECURSE RENDER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/*.cpp)
file(GLOB_RECURSE UTIL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/*.cpp)

set(
    LIB_SRC 
    ${CORE_SRC} 
    ${LOGGER_SRC} 
    ${GUI_SRC}
    ${PLATFORM_SRC}
    ${RENDER_SRC} 
    ${UTIL_SRC}
)

add_library( JadeiteLiteLib STATIC ${LIB_SRC} )


# ------------------------------------------------------------
# Target Include directories
# ------------------------------------------------------------
target_include_directories(
        JadeiteLiteLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
 
target_include_directories(JadeiteLiteLib PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends ) 

# Use Precompiled Headers
target_precompile_headers(JadeiteLiteLib REUSE_FROM PCH)

target_link_libraries(
    JadeiteLiteLib 
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
    glm::glm
    glad::glad
    fmt::fmt
    soil2
    EnTT::EnTT
    imgui
)

target_compile_options(
    JadeiteLiteLib
    PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAGS}>
)
