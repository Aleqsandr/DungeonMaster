file(GLOB HEADER_FILES headers/*.hpp)
file(GLOB SRC_FILES sources/*.cpp)
file(GLOB_RECURSE SHADER_FILES shaders/*.glsl)
set(SRC_FILES ${SRC_FILES} dunjeonmaster.cpp)

    add_executable(DunjeonMaster ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
    target_link_libraries(DunjeonMaster ${ALL_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY headers DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY sources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
