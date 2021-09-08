set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/*.h)

message(6502-emulator-core)
message("System name:           " ${CMAKE_SYSTEM_NAME})
message("Sources dir:           " ${SOURCES_DIR})
message("Sources:               " ${SOURCES})
message("Headers:               " ${HEADERS})
message("")

add_library(6502-emulator-core ${SOURCES} ${HEADERS})

set_target_properties(
	6502-emulator-core PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(6502-emulator-core PRIVATE ${SOURCES_DIR})