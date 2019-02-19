cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

project(NDNup VERSION 0.1 LANGUAGES C)

option(BUILD_DOC          "Build documentation"   ON)
option(BUILD_DEBUG        "Build with debug"      ON)


if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen not found")
    endif (DOXYGEN_FOUND)
endif (BUILD_DOC)

add_library(NDNup STATIC
    src/tlv_encode.c
    src/tlv_decode.c
    src/ndnup_buffer.c
    src/interest.c
)

target_include_directories(NDNup PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

include(CTest)
if (BUILD_TESTING)
    add_library(unity STATIC "Unity/src/unity.c")
    target_include_directories(unity PUBLIC "Unity/src")

    add_executable(unittest-ndnup
        "${CMAKE_CURRENT_SOURCE_DIR}/test/test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/test_tlv_encode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/test_tlv_decode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/test_interest_encode.c"
        )
    target_link_libraries(unittest-ndnup unity NDNup)
    add_test(ndnup-tests unittest-ndnup)
endif (BUILD_TESTING)
