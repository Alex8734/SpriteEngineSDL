# Editor/CMakeLists.txt

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
set(CMAKE_BUILD_TYPE Debug) # CHANGE WHEN BUILDING IN RELEASE TO Release
# !!!!!!!!!!!!!!!

file(GLOB_RECURSE EDITOR_SOURCE_FILES
    "Source/*.cpp"
    "Source/*.h"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EDITOR_SOURCE_FILES})

add_executable(${EDITOR_NAME}
    ${EDITOR_SOURCE_FILES}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Link libraries
target_link_libraries(${EDITOR_NAME} PRIVATE
    Core
)

# Set debug and release directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Editor/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Editor/Release)

# Path to the SFML DLLs after build
set(SFML_DLL_DIR "${CMAKE_BINARY_DIR}/ThirdParty/sfml/lib")

# Custom command to copy DLLs based on build configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET ${EDITOR_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Debug/sfml-audio-d-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Debug/sfml-graphics-d-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Debug/sfml-network-d-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Debug/sfml-system-d-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Debug/sfml-window-d-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${EDITOR_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Release/sfml-audio-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Release/sfml-graphics-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Release/sfml-network-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Release/sfml-system-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_DLL_DIR}/Release/sfml-window-2.dll $<TARGET_FILE_DIR:${EDITOR_NAME}>
    )
endif()

if(MSVC)
    target_compile_options(${EDITOR_NAME} PRIVATE /W4)
    add_compile_options(/MP)
endif()