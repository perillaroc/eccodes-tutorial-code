project(get_grib_info)

set(SOURCE_FILES main.cpp)

include_directories(${ECCODES_INCLUDE_DIR})
link_libraries(${ECCODES_LIBRARY})

add_executable(get_grib_info ${SOURCE_FILES})