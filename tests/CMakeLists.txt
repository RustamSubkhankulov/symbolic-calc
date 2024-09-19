enable_testing()

set(TEST_SRC_DIR src)
get_filename_component(PARENT_DIR ../ ABSOLUTE)

macro(TEST_TARGET NAME SOURCE)
  add_executable(${NAME} ${TEST_SRC_DIR}/${SOURCE}.cpp)

  set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)
  set_target_properties(
    ${NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PARENT_DIR}/bin
    )
  
  target_link_libraries(${NAME} PRIVATE GTest::GTest)
  target_link_libraries(${NAME} PRIVATE calc)

  add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()

find_package(GTest)
if (NOT GTest_FOUND)
  include(FetchContent)

  option(BUILD_GMOCK OFF)
  option(INSTALL_GTEST OFF)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
  )
  FetchContent_MakeAvailable(googletest)

  add_library(GTest::GTest INTERFACE IMPORTED)
  target_link_libraries(GTest::GTest INTERFACE gtest_main)
endif()

TEST_TARGET(test-evaluation evaluation)
TEST_TARGET(test-prioritization prioritization)
TEST_TARGET(test-variables variables)
