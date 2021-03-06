cmake_minimum_required(VERSION 3.10)

# Install C++ plugin in Netbeans:
# https://stackoverflow.com/questions/51493882/netbeans-9-c-support
# Use plugins url:
# http://updates.netbeans.org/netbeans/updates/8.2/uc/final/distribution/catalog.xml.gz

# On Ubuntu 18.04:
# version=3.14
# build=5
# mkdir ~/temp
# cd ~/temp
# wget https://cmake.org/files/v$version/cmake-$version.$build-Linux-x86_64.sh 
# sudo mkdir /opt/cmake
# sudo sh cmake-$version.$build-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
# sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

#################################################################
# The project is supposed to be homogenous C++17 and Fortran.
# (Fortran is needed for proper linkage with blas and lapack.)
project(onerut LANGUAGES CXX Fortran)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall)
add_compile_options(-pedantic)
#add_compile_options(-ffast-math) 
add_compile_options(-pthread)
# Note: fast-math disables isnan that is used in a test module.
# When fast-math is enable the concerning NaN values may fail.

# On Ubuntu 18.04:
# sudo add-apt-repository ppa:ubuntu-toolchain-r/test
# sudo apt-get update
# sudo apt-get install gcc-8 g++-8 gfortran-8
# gcc-8 --version; g++-8 --version; gfortran-8 --version;
# sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7 --slave /usr/bin/gfortran gfortran /usr/bin/gfortran-7 
# sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8 --slave /usr/bin/gfortran gfortran /usr/bin/gfortran-8 
# gcc --version; g++ --version; gfortran --version;
# update-alternatives --query gcc
# sudo update-alternatives --config gcc # to change the alternative. 

#################################################################
if (NOT (UNIX OR CYGWIN))
  message(WARNING "The project is supposed to be compiled on linux.")
endif()
if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  message(WARNING "The project is supposed to be compiled with gcc.")
endif()

#################################################################
# Define important directories.
set(EXTERNAL_PACKAGES_ROOT "${CMAKE_SOURCE_DIR}/external_packages" )
include_directories(BEFORE SYSTEM "${EXTERNAL_PACKAGES_ROOT}/include")
link_directories(BEFORE SYSTEM "${EXTERNAL_PACKAGES_ROOT}/lib")

#set (CMAKE_MODULE_PATH "${EXTERNAL_PACKAGES_ROOT}/share/Armadillo/CMake")

#################################################################
message("-----------------------------------")
message("---  external_packages  -----------")
message("-----------------------------------")

message("\${EXTERNAL_PACKAGES_ROOT}:                              ${EXTERNAL_PACKAGES_ROOT}")
message("Content of the \${EXTERNAL_PACKAGES_ROOT} directory:")
find_library(EXTERNAL_PACKAGES_BOOST_PROGRAM_OPTIONS_LIBRARY_PATH boost_program_options PATHS "${EXTERNAL_PACKAGES_ROOT}/lib" NO_DEFAULT_PATH)
find_library(EXTERNAL_PACKAGES_BOOST_SYSTEM_LIBRARY_PATH boost_system PATHS "${EXTERNAL_PACKAGES_ROOT}/lib" NO_DEFAULT_PATH)
find_library(EXTERNAL_PACKAGES_BLAS_LIBRARY_PATH blas PATHS "${EXTERNAL_PACKAGES_ROOT}/lib" NO_DEFAULT_PATH)
find_library(EXTERNAL_PACKAGES_LAPACK_LIBRARY_PATH lapack PATHS "${EXTERNAL_PACKAGES_ROOT}/lib" NO_DEFAULT_PATH)
find_library(EXTERNAL_PACKAGES_ARMADILLO_LIBRARY_PATH armadillo PATHS "${EXTERNAL_PACKAGES_ROOT}/lib" NO_DEFAULT_PATH)
message("  EXTERNAL_PACKAGES_BOOST_PROGRAM_OPTIONS_LIBRARY_PATH: ${EXTERNAL_PACKAGES_BOOST_PROGRAM_OPTIONS_LIBRARY_PATH}" )
message("  EXTERNAL_PACKAGES_BOOST_SYSTEM_LIBRARY_PATH:          ${EXTERNAL_PACKAGES_BOOST_SYSTEM_LIBRARY_PATH}" )
message("  EXTERNAL_PACKAGES_BLAS_LIBRARY_PATH:                  ${EXTERNAL_PACKAGES_BLAS_LIBRARY_PATH}" )
message("  EXTERNAL_PACKAGES_LAPACK_LIBRARY_PATH:                ${EXTERNAL_PACKAGES_LAPACK_LIBRARY_PATH}" )
message("  EXTERNAL_PACKAGES_ARMADILLO_LIBRARY_PATH:             ${EXTERNAL_PACKAGES_ARMADILLO_LIBRARY_PATH}" )

#################################################################
message("-----------------------------------")
message("---  boost - imported data  -------")
message("-----------------------------------")

set(BOOST_ROOT "${EXTERNAL_PACKAGES_ROOT}")
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED system program_options)

message("\${Boost_LIBRARY_DIRS}: ${Boost_LIBRARY_DIRS}")
message("\${Boost_INCLUDE_DIRS}: ${Boost_INCLUDE_DIRS}")
message("\${Boost_LIBRARIES}:    ${Boost_LIBRARIES}")
if (TARGET Boost::boost)
  message("Boost::boost is a target.")
  get_target_property(x Boost::boost NAME)
    message("  Boost::boost.NAME:                          ${x}")
  get_target_property(x Boost::boost TYPE)
    message("  Boost::boost.TYPE:                          ${x}")
  get_target_property(x Boost::boost INTERFACE_INCLUDE_DIRECTORIES)
    message("  Boost::boost.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
else()
  message(FATAL_ERROR "Boost::boost is not a target!")
endif()

if (TARGET Boost::program_options)
  message("Boost::program_options is a target.")
  get_target_property(x Boost::program_options NAME)
    message("  Boost::program_options.NAME:                          ${x}")
  get_target_property(x Boost::program_options TYPE)
    message("  Boost::program_options.TYPE:                          ${x}")
  get_target_property(x Boost::program_options LOCATION)
    message("  Boost::program_options.LOCATION:                      ${x}")
  get_target_property(x Boost::program_options INTERFACE_INCLUDE_DIRECTORIES)
    message("  Boost::program_options.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
  get_target_property(x Boost::program_options INTERFACE_LINK_LIBRARIES)
    message("  Boost::program_options.INTERFACE_LINK_LIBRARIES:      ${x}")
else()
  message(FATAL_ERROR "Boost::program_options is not a target!")
endif()

if (TARGET Boost::system)
  message("Boost::system is a target.")
  get_target_property(x Boost::system NAME)
    message("  Boost::system.NAME:                          ${x}")
  get_target_property(x Boost::system TYPE)
    message("  Boost::system.TYPE:                          ${x}")
  get_target_property(x Boost::system LOCATION)
    message("  Boost::system.LOCATION:                      ${x}")
  get_target_property(x Boost::system INTERFACE_INCLUDE_DIRECTORIES)
    message("  Boost::system.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
  get_target_property(x Boost::system INTERFACE_LINK_LIBRARIES)
    message("  Boost::system.INTERFACE_LINK_LIBRARIES:      ${x}")
else()
  message(FATAL_ERROR "Boost::system is not a target!")
endif()

#################################################################
message("-----------------------------------")
message("---  armadillo - imported data  ---")
message("-----------------------------------")

find_package(Armadillo REQUIRED CONFIG PATHS "${CMAKE_SOURCE_DIR}/external_packages/share/Armadillo/CMake" NO_DEFAULT_PATH)
message("\${ARMADILLO_LIBRARY_DIRS}: ${ARMADILLO_LIBRARY_DIRS}")
message("\${ARMADILLO_INCLUDE_DIRS}: ${ARMADILLO_INCLUDE_DIRS}")
message("\${ARMADILLO_LIBRARIES}:    ${ARMADILLO_LIBRARIES}")
if (TARGET ${ARMADILLO_LIBRARIES})
  message("\${ARMADILLO_LIBRARIES} is a target.")
  get_target_property(x ${ARMADILLO_LIBRARIES} NAME)
    message("  \${ARMADILLO_LIBRARIES}.NAME:                          ${x}")
  get_target_property(x ${ARMADILLO_LIBRARIES} TYPE)
    message("  \${ARMADILLO_LIBRARIES}.TYPE:                          ${x}")
  get_target_property(x ${ARMADILLO_LIBRARIES} LOCATION)
    message("  \${ARMADILLO_LIBRARIES}.LOCATION:                      ${x}")
  get_target_property(x ${ARMADILLO_LIBRARIES} INTERFACE_INCLUDE_DIRECTORIES)
    message("  \${ARMADILLO_LIBRARIES}.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
  get_target_property(x ${ARMADILLO_LIBRARIES} INTERFACE_LINK_LIBRARIES)
    message("  \${ARMADILLO_LIBRARIES}.INTERFACE_LINK_LIBRARIES:      ${x}")
else()
  message(FATAL_ERROR "${ARMADILLO_LIBRARIES} is not a target!")
endif()

#################################################################
message("-----------------------------------")
message("---  lapack - imported data  ------")
message("-----------------------------------")

# The data about lapack is not used bu  this cmake file.
# Lapack should be detected by armadillo during its build
# and the data should be intercorporated into armadillo target. 
# Here The data about lapack are found only for messaging information:

include("${CMAKE_SOURCE_DIR}/external_packages/lib/cmake/lapack-3.8.0/lapack-config.cmake")

message("\${LAPACK_blas_LIBRARIES}: ${LAPACK_blas_LIBRARIES}")
if (TARGET ${LAPACK_blas_LIBRARIES})
  message("\${LAPACK_blas_LIBRARIES} is a target.")
  get_target_property(x ${LAPACK_blas_LIBRARIES} NAME)
    message("  \${LAPACK_blas_LIBRARIES}.NAME:                          ${x}")
  get_target_property(x ${LAPACK_blas_LIBRARIES} TYPE)
    message("  \${LAPACK_blas_LIBRARIES}.TYPE:                          ${x}")
  get_target_property(x ${LAPACK_blas_LIBRARIES} LOCATION)
    message("  \${LAPACK_blas_LIBRARIES}.LOCATION:                      ${x}")
  get_target_property(x ${LAPACK_blas_LIBRARIES} INTERFACE_INCLUDE_DIRECTORIES)
    message("  \${LAPACK_blas_LIBRARIES}.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
  get_target_property(x ${LAPACK_blas_LIBRARIES} INTERFACE_LINK_LIBRARIES)
    message("  \${LAPACK_blas_LIBRARIES}.INTERFACE_LINK_LIBRARIES:      ${x}")
else()
  message(SEND_ERROR "${LAPACK_blas_LIBRARIES} is not a target!")
endif()
message("\${LAPACK_lapack_LIBRARIES}: ${LAPACK_lapack_LIBRARIES}")
if (TARGET ${LAPACK_lapack_LIBRARIES})
  message("\${LAPACK_lapack_LIBRARIES} is a target.")
  get_target_property(x ${LAPACK_lapack_LIBRARIES} NAME)
    message("  \${LAPACK_lapack_LIBRARIES}.NAME:                          ${x}")
  get_target_property(x ${LAPACK_lapack_LIBRARIES} TYPE)
    message("  \${LAPACK_lapack_LIBRARIES}.TYPE:                          ${x}")
  get_target_property(x ${LAPACK_lapack_LIBRARIES} LOCATION)
    message("  \${LAPACK_lapack_LIBRARIES}.LOCATION:                      ${x}")
  get_target_property(x ${LAPACK_lapack_LIBRARIES} INTERFACE_INCLUDE_DIRECTORIES)
    message("  \${LAPACK_lapack_LIBRARIES}.INTERFACE_INCLUDE_DIRECTORIES: ${x}")
  get_target_property(x ${LAPACK_lapack_LIBRARIES} INTERFACE_LINK_LIBRARIES)
    message("  \${LAPACK_lapack_LIBRARIES}.INTERFACE_LINK_LIBRARIES:      ${x}")
else()
  message(SEND_ERROR "${LAPACK_lapack_LIBRARIES} is not a target!")
endif()

#################################################################
message("-----------------------------------")
message("---  gtest - imported data  -------")
message("-----------------------------------")

# https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/

# On Ubuntu 18.04:
# sudo apt-get install cmake libgtest-dev
# cd /usr/src/gtest
# sudo cmake CMakeLists.txt
# sudo make
# sudo cp *.a /usr/lib

find_package(GTest REQUIRED)
message("\${GTEST_INCLUDE_DIRS}: ${GTEST_INCLUDE_DIRS}")
message("\${GTEST_LIBRARIES}:    ${GTEST_LIBRARIES}")

#################################################################
message("-----------------------------------")
message("---  the project  -----------------")
message("-----------------------------------")

add_subdirectory(esc)
add_subdirectory(string_utils)
add_subdirectory(log_utils)
add_subdirectory(onerut_dependence)
add_subdirectory(onerut_scalar)
add_subdirectory(onerut_scalar_tests)
add_subdirectory(onerut_env)
add_subdirectory(onerut_typed_operator)
add_subdirectory(onerut_typed_operator_tests)
add_subdirectory(onerut_normal_operator)
add_subdirectory(onerut_normal_operator_tests)
add_subdirectory(onerut_convergence_parameter)
add_subdirectory(onerut_request)
add_subdirectory(onerut_parser_exec)
add_subdirectory(onerut_parser_exec_tests)
add_subdirectory(onerut_parser_rules)
add_subdirectory(onerut_parser_rules_tests)
add_subdirectory(onerut)

