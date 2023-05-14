include(FetchContent)
FetchContent_Declare(
 	googletest
  	GIT_REPOSITORY https://github.com/google/googletest.git
  	GIT_TAG        release-1.10.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(EXECUTABLE_OUTPUT_PATH "${${PROJECT_NAME}_BINARY_DIR}")

add_executable(unit_tests test_engine.cpp)
set_target_properties(unit_tests PROPERTIES FOLDER "./" CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
add_test(unit_tests_build "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target unit_tests)
add_test(unit_tests_run ${EXECUTABLE_OUTPUT_PATH}/unit_tests)
set_tests_properties(unit_tests_run PROPERTIES DEPENDS unit_tests_build)
target_link_libraries(unit_tests gtest gtest_main autograd::autograd)