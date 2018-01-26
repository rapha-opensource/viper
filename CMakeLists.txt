cmake_minimum_required (VERSION 3.0)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()
project (Viper)
set (CMAKE_CXX_STANDARD 14)
add_subdirectory(tests)
