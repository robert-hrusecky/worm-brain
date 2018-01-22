add_executable(worm-brain ${srcs})

target_compile_options(worm-brain PRIVATE "-Wall")

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(worm-brain PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(worm-brain "${CMAKE_THREAD_LIBS_INIT}")
endif()

target_link_libraries(worm-brain ${OPENGL_LIBRARY})
target_link_libraries(worm-brain ${GLEW_LIBRARIES})
target_link_libraries(worm-brain ${SDL2_LIBRARIES})
target_link_libraries(worm-brain ${SDL2_MIXER_LIBRARIES})
target_link_libraries(worm-brain ${BOX2D_LIBRARIES})
target_link_libraries(worm-brain optimized ${SNOW_ENGINE_LIBRARY} debug ${SNOW_ENGINE_DEBUG_LIBRARY})