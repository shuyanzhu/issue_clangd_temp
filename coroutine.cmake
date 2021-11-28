if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    EXECUTE_PROCESS( COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE clang_full_version_string )
    string (REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION_STRING ${clang_full_version_string})
    if("${CLANG_VERSION_STRING}" VERSION_GREATER_EQUAL 10 AND "${CLANG_VERSION_STRING}" VERSION_LESS_EQUAL 13)
        add_definitions(-DUSE_CLANG_EXP)
    elseif("${CLANG_VERSION_STRING}" VERSION_LESS 10)
        message(FATAL_ERROR "Using clang version < 10")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wl,-rpath,/home/zhm/bin/llvm/lib -Wno-unused-command-line-argument") # clang++
#     set(LIBRARIES_TO_LINK "c++abi")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    EXECUTE_PROCESS( COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GXX_VERSION_STRING)
    if("${GXX_VERSION_STRING}" VERSION_LESS 10)
        message(FATAL_ERROR "Using g++ version < 10")
    elseif("${GXX_VERSION_STRING}" VERSION_EQUAL 10)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
    message(FATAL_ERROR "Not support ICC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
    message("Using MSVC, hadn't detect MSVC version")
endif()