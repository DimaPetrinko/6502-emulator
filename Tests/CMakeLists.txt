set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXTERNAL_INCLUDE_DIR ${CORE_LIB_DIR}/src)

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/*.h)

message(Tests)
message("System name:           " ${CMAKE_SYSTEM_NAME})
message("Sources dir:           " ${SOURCES_DIR})
message("Include dir:           " ${EXTERNAL_INCLUDE_DIR})
message("Sources:               " ${SOURCES})
message("Headers:               " ${HEADERS})
message("")

add_executable(Tests ${SOURCES} ${HEADERS})

set_target_properties(
	Tests PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(Tests PRIVATE ${EXTERNAL_INCLUDE_DIR})
target_include_directories(Tests PRIVATE ${SOURCES_DIR})
target_link_libraries(Tests 6502-emulator-core)