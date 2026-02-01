include(FetchContent)

FetchContent_Declare(
  filedialog
  GIT_REPOSITORY https://github.com/aiekick/ImGuiFileDialog
  GIT_TAG        v0.6.8
  GIT_SHALLOW    1
)

FetchContent_MakeAvailable(filedialog)

target_link_libraries(ImGuiFileDialog PUBLIC imgui)

# Gather all sources from all folders 
file(GLOB_RECURSE WINDOW_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/*.cpp)

set(
    APP_SRC 
    ${WINDOW_SRC} 
    src/application.cpp 
    src/main.cpp
)

add_executable( JadeiteLite ${APP_SRC} ${APP_ICON_RESOURCE} )


# ------------------------------------------------------------
# Target Include directories
# ------------------------------------------------------------
target_include_directories(
        JadeiteLite PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
 
# Use Precompiled Headers
target_precompile_headers(JadeiteLite REUSE_FROM PCH)

target_link_libraries(
    JadeiteLite 
    PRIVATE
    JadeiteLiteLib
    ImGuiFileDialog
)

target_compile_options(
    JadeiteLite 
    PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAGS}>
)
