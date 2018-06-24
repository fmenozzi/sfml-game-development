# Create main executable target.
add_executable(main main.cpp game.cpp)
target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_compile_definitions(main PRIVATE RESOURCE_DIRECTORY="${PROJECT_SOURCE_DIR}/res/")
