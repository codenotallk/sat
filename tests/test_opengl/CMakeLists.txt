if (${SAT_OPENGL})
    add_executable (test_sat_opengl_window ${CMAKE_CURRENT_LIST_DIR}/test_sat_opengl_window.c)
    target_link_libraries (test_sat_opengl_window PUBLIC sat)
    add_test (NAME test_sat_opengl_window COMMAND test_sat_opengl_window ${CMAKE_CURRENT_LIST_DIR})

    add_executable (test_sat_opengl_program ${CMAKE_CURRENT_LIST_DIR}/test_sat_opengl_program.c)
    target_link_libraries (test_sat_opengl_program PUBLIC sat)
    add_test (NAME test_sat_opengl_program COMMAND test_sat_opengl_program ${CMAKE_CURRENT_LIST_DIR})

    add_executable (test_sat_opengl_triangle ${CMAKE_CURRENT_LIST_DIR}/test_sat_opengl_triangle.c)
    target_link_libraries (test_sat_opengl_triangle PUBLIC sat)
    add_test (NAME test_sat_opengl_triangle COMMAND test_sat_opengl_triangle ${CMAKE_CURRENT_LIST_DIR})
endif ()