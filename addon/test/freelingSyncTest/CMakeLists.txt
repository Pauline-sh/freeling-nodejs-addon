cmake_minimum_required(VERSION 2.8)

project(freelingSyncTest)

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

    add_executable(${PROJECT_NAME} "main.cpp")

    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${ICU_LIBRARIES} )
    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} )
    target_link_libraries(${PROJECT_NAME} /usr/local/lib/libfreeling.so)
endif()
