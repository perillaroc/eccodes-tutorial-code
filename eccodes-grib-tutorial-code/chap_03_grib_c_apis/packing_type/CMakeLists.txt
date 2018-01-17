set(project_name packing_type)

project(${project_name})

set(SOURCE_FILES main.cpp)

include_directories(${ECCODES_INCLUDE_DIR})
link_libraries(${ECCODES_LIBRARY})

add_executable(${project_name} ${SOURCE_FILES})