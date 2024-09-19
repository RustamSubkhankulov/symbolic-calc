set(DRIVER_SRC_DIR src)
set(DRIVER_INC_DIR inc)

file(GLOB DRIVER_SOURCES CONFIGURE_DEPENDS ${DRIVER_SRC_DIR}/*.c)
get_filename_component(PARENT_DIR ../ ABSOLUTE)

add_executable(driver ${DRIVER_SOURCES})
set_target_properties(
  driver PROPERTIES 
  RUNTIME_OUTPUT_DIRECTORY ${PARENT_DIR}/bin
  )

target_link_libraries(driver PRIVATE ${PROJECT_NAME})
target_include_directories(driver PRIVATE ${DRIVER_INC_DIR})
