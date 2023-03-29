cmake_minimum_required(VERSION 3.2)

project(IpFilter)

add_executable(ip_filter ip_filter1.cpp)

target_compile_features(ip_filter PUBLIC cxx_std_17)

set_target_properties(ip_filter PROPERTIES CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(ip_filter PRIVATE /W4 /WX)

else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror)
endif()