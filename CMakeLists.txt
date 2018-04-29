cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add source files
file(GLOB SOURCES
    src/test.cpp
    src/snippets/*.hpp
    src/snippets/*.cpp
)

# link gtest
add_executable(runtests ${SOURCES})
target_link_libraries(runtests ${GTEST_LIBRARIES} pthread)

# we are too lazy
add_custom_command(
    TARGET runtests POST_BUILD
    COMMAND ./runtests
    COMMAND python3 make_snippets.py src/snippets/ UltiSnips/)
