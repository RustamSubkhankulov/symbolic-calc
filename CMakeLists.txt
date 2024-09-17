cmake_minimum_required(VERSION 3.21)

project(
        calc
        DESCRIPTION "Simple symbolic expression calculator"
        LANGUAGES C
        )

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE is not specified, using Release by default")
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

set(SRC_DIR src)
set(INC_DIR inc)
set(INC_PRIVATE_DIR inc-private)

find_package(FLEX REQUIRED)
if (NOT FLEX_FOUND)
  error("Failed to find Flex package")
endif()
file(GLOB FLEX_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lex/*.l)
FLEX_TARGET(lexer ${FLEX_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/lex.c)

FIND_PACKAGE(BISON REQUIRED)
if (NOT BISON_FOUND)
  error("Failed to find Bison package")
endif()
file(GLOB BISON_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/yacc/*.y)
BISON_TARGET(parser ${BISON_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/yacc.c)

file(GLOB SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.c)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} 
  ${SOURCES}
  ${FLEX_lexer_OUTPUTS}
  ${BISON_parser_OUTPUTS}
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_PRIVATE_DIR})

option(VERBOSE_LEX "Dump tokenization process" OFF)
if (VERBOSE_LEX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DVERBOSE_LEX)
endif()

option(VERBOSE_YACC "Dump parsing process" OFF)
if (VERBOSE_YACC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DVERBOSE_YACC)
endif()
