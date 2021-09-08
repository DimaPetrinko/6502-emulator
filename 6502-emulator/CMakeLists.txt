set(INSTALL_DIR ${CMAKE_BINARY_DIR}/install/${CMAKE_PROJECT_NAME})
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(EXTERNAL_INCLUDE_DIR ${CORE_LIB_DIR}/src)

file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/*.h)

message(6502-emulator)
message("System name:           " ${CMAKE_SYSTEM_NAME})
message("Install dir:           " ${INSTALL_DIR})
message("Sources dir:           " ${SOURCES_DIR})
message("Resources dir:         " ${RESOURCES_DIR})
message("Include dir:           " ${EXTERNAL_INCLUDE_DIR})
message("Sources:               " ${SOURCES})
message("Headers:               " ${HEADERS})
message("")

add_executable(6502-emulator ${SOURCES} ${HEADERS})

set_target_properties(
	6502-emulator PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(6502-emulator PRIVATE ${EXTERNAL_INCLUDE_DIR})
target_include_directories(6502-emulator PRIVATE ${SOURCES_DIR})
target_link_libraries(6502-emulator 6502-emulator-core)

install(TARGETS 6502-emulator DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RESOURCES_DIR} DESTINATION ${INSTALL_DIR})