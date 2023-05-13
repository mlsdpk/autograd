add_executable(autograd_example main.cpp)
set_target_properties(autograd_example PROPERTIES FOLDER "Examples")
target_link_libraries(autograd_example PRIVATE autograd::autograd)  # adds the "#include" directory.