set(SOURCE_FILES
    main.cpp
    Window.cpp
    Shader.cpp
    Circle.cpp
)

add_executable(
    balls
    glad.c
    ${SOURCE_FILES}
)

target_link_libraries(balls PRIVATE
    glfw
    m
)

set(PROJECT_FILES
    simple.vert
    simple.frag
)

get_target_property(
    OUTPUT_FOLDER balls
    RUNTIME_OUTPUT_DIRECTORY
)

add_custom_target("copy_files" ALL DEPENDS ${PROJECT_FILES})
foreach(filename ${PROJECT_FILES})
    add_custom_command(
        OUTPUT ${OUTPUT_FOLDER}/${filename}
            COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
                ${OUTPUT_FOLDER}
                DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endforeach()
