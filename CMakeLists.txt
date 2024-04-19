cmake_minimum_required(VERSION 3.28.3)

project(EcsApiExample)
set(BOOL EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(api_source_dir "${PROJECT_SOURCE_DIR}/api/src")
set(test_source_dir "${PROJECT_SOURCE_DIR}/test/src")

set(api_include_dir "${PROJECT_SOURCE_DIR}/api/include")
set(test_include_dir "${PROJECT_SOURCE_DIR}/test/include")

include_directories(${api_include_dir})
include_directories(${test_include_dir})

file(GLOB api_source_cpp_files "${api_source_dir}/*.cpp")
file(GLOB api_include_hpp_files "${api_include_dir}/*.hpp")

file(GLOB test_source_cpp_files "${test_source_dir}/*.cpp")
file(GLOB test_include_hpp_files "${test_include_dir}/*.hpp")

add_executable(EcsApiExample ${api_include_hpp_files} ${api_source_cpp_files}
                             ${test_include_hpp_files} ${test_source_cpp_files})

# target_link_libraries()
target_compile_features(EcsApiExample PUBLIC cxx_std_23)
