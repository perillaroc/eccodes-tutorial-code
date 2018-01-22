include(CheckIncludeFile)

find_path(
        ECCODES_INCLUDE_DIR eccodes.h
        HINTS /usr/include /usr/local/include
        NO_DEFAULT_PATH
)

find_library(
        ECCODES_LIBRARY
        eccodes
        /usr/lib  /usr/local/lib ${ECCODES_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

add_subdirectory(chap_03_grib_c_apis)
add_subdirectory(chap_06_advanced_topics)