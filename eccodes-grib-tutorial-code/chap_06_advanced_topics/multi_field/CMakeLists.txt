project(multi_field)

set(SOURCE_FILES main.cpp)

include_directories(${ECCODES_INCLUDE_DIR})
link_libraries(${ECCODES_LIBRARY})

add_executable(multi_field ${SOURCE_FILES})