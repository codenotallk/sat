if (${SAT_SDL})

    message (STATUS "SAT_SDL support enable")

    list (APPEND SAT_SOURCES ${CMAKE_SOURCE_DIR}/src/sat_sdl.c
                             ${CMAKE_SOURCE_DIR}/src/sat_sdl/sat_sdl_window.c
                             ${CMAKE_SOURCE_DIR}/src/sat_sdl/sat_sdl_keys.c
                             ${CMAKE_SOURCE_DIR}/src/sat_sdl/sat_sdl_image.c)

    list (APPEND SAT_INCLUDES ${CMAKE_SOURCE_DIR}/include/sat_sdl)
    file (APPEND ${CMAKE_SOURCE_DIR}/include/sat_optionals.h "#include <sat_sdl.h>\n")

    list (APPEND SAT_LIBRARIES SDL2 SDL2_image SDL2_ttf SDL2_mixer)

    install (FILES include/sat_sdl.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install (FILES include/sat_sdl/sat_sdl_types.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif ()