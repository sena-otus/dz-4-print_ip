cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

# underscores are not allowed in deb package name, but adding underscore to comply with requirements...
project(print_ip VERSION ${PROJECT_VERSION})

option(WITH_TEST "Whether to build Google test" ON)
option(WITH_CLANG_TIDY "use clang-tidy" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WITH_CLANG_TIDY)
  find_program(CLANGTIDY NAMES clang-tidy-15 clang-tidy-14 clang-tidy REQUIRED)
  set(CMAKE_CXX_CLANG_TIDY "${CLANGTIDY}")
  message(NOTICE "found and enabled CLANGTIDY=${CLANGTIDY}")
endif()

configure_file(version.h.in version.h)

add_executable(print_ip main.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip
    PRIVATE "${CMAKE_BINARY_DIR}"
  )

if(WITH_TEST)
    find_package(GTest REQUIRED)
    enable_testing()

    add_executable(gtest_print_ip gtest_print_ip.cpp)

    set_target_properties(gtest_print_ip PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(gtest_print_ip
	GTest::gtest_main
    )

    gtest_discover_tests(gtest_print_ip)
endif()


if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --all-warnings -Wall -Werror -Wextra -pedantic")
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
