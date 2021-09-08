cmake_minimum_required(VERSION 3.0.0)
project(6502-emulator VERSION 0.1.0)

set(CORE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/6502-emulator-core)

# CTest generates a bunch of targets
# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_subdirectory(6502-emulator-core)
add_subdirectory(6502-emulator)
add_subdirectory(Tests)