cmake_minimum_required(VERSION 3.21)

project(
        calc
        DESCRIPTION "Simple symbolic expression calculator"
        LANGUAGES C
        )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE is not specified, using Release by default")
endif()

set(LIB_SRC_DIR src)
set(LIB_INC_DIR inc)
set(LIB_INC_PRIVATE_DIR inc-private)

set(TESTS_DIR tests)
set(DRIVER_DIR driver)


find_package(FLEX REQUIRED)
if (NOT FLEX_FOUND)
  error("Failed to find Flex package")
endif()
file(GLOB FLEX_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lex/*.l)
FLEX_TARGET(lexer ${FLEX_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/lex.c)

find_package(BISON REQUIRED)
if (NOT BISON_FOUND)
  error("Failed to find Bison package")
endif()
file(GLOB BISON_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/yacc/*.y)
BISON_TARGET(parser ${BISON_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/yacc.c)

file(GLOB LIB_SOURCES CONFIGURE_DEPENDS ${LIB_SRC_DIR}/*.c)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(${PROJECT_NAME} 
  ${LIB_SOURCES}
  ${FLEX_lexer_OUTPUTS}
  ${BISON_parser_OUTPUTS}
  )

target_link_libraries(${PROJECT_NAME} m)

target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INC_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_INC_PRIVATE_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${LIB_INC_DIR}/calc.h)


option(VERBOSE_LEX "Dump tokenization process" OFF)
if (VERBOSE_LEX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DVERBOSE_LEX)
endif()

option(VERBOSE_YACC "Dump parsing process" OFF)
if (VERBOSE_YACC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DVERBOSE_YACC)
endif()


set(CMAKE_INSTALL_PREFIX "")

install(
        TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION inc/${PROJECT_NAME}
        )

# add_subdirectory(${TESTS_DIR})
add_subdirectory(${DRIVER_DIR})
