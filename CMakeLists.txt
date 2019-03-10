cmake_minimum_required(VERSION 2.8)

project(freeling)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

enable_language(CXX)

find_package(Boost 1.65.1 COMPONENTS filesystem system regex thread program_options)
find_package(ICU 60.2)
find_package(ZLIB 1.2.11)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories( ${ICU_INCLUDE_DIRS} )
    include_directories( ${ZLIB_INCLUDE_DIRS} )

    set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/addon_utils.cpp
        ${CMAKE_SOURCE_DIR}/src/word.cpp
        ${CMAKE_SOURCE_DIR}/src/sentence.cpp
        ${CMAKE_SOURCE_DIR}/src/tokenizer.cpp
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/analysis.cpp
        ${CMAKE_SOURCE_DIR}/src/splitter.cpp
        ${CMAKE_SOURCE_DIR}/src/morfo.cpp
    )
    set(HEADERS
        ${CMAKE_SOURCE_DIR}/include/addon_utils.h
        ${CMAKE_SOURCE_DIR}/include/addon_errors.h
        ${CMAKE_SOURCE_DIR}/include/word.h
        ${CMAKE_SOURCE_DIR}/include/sentence.h
        ${CMAKE_SOURCE_DIR}/include/tokenizer.h
        ${CMAKE_SOURCE_DIR}/include/analysis.h
        ${CMAKE_SOURCE_DIR}/include/splitter.h
        ${CMAKE_SOURCE_DIR}/include/morfo.h
    )

    add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".node")
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api
        ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api/src
        ${CMAKE_JS_INC})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${ICU_LIBRARIES} )
    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} )
    target_link_libraries(${PROJECT_NAME} /usr/local/lib/libfreeling.so)
endif()
