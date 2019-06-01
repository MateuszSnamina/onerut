#!/bin/bash
set -u

jobs=4

#################################################################

function init() {
  cd `dirname "$0"`
  if [ -f 'external_packages' ]; then
    echo 'Error: "external_packages" is supposed to be a subfolder.' >&2
    exit 1 
  fi
  [ -d 'external_packages' ] || mkdir 'external_packages'
  cd 'external_packages'
  EP_PATH=`pwd`
  mkdir -p "${EP_PATH}/include/"
  mkdir -p "${EP_PATH}/lib/"
  readonly exprtk_wget_log_path="${EP_PATH}/exprtk_wget_log_path.log"
  readonly boost_wget_log_path="${EP_PATH}/boost_wget.log"
  readonly boost_boostrap_log_path="${EP_PATH}/boost_boostrap.log"
  readonly boost_bjam_log_path="${EP_PATH}/boost_bjam.log"
  readonly lapack_wget_log_path="${EP_PATH}/lapack_wget.log"
  readonly lapack_cmake_log_path="${EP_PATH}/lapack_cmake.log"
  readonly lapack_make_log_path="${EP_PATH}/lapack_make.log"
  readonly lapack_make_install_log_path="${EP_PATH}/lapack_make_install.log"
  readonly armadillo_wget_log_path="${EP_PATH}/armadillo_wget.log"
  readonly armadillo_cmake_log_path="${EP_PATH}/armadillo_cmake.log"
  readonly armadillo_make_log_path="${EP_PATH}/armadillo_make.log"
  readonly armadillo_make_install_log_path="${EP_PATH}/armadillo_make_install.log"
  readonly openblas_wget_log_path="${EP_PATH}/openblas_wget.log"
  readonly openblas_cmake_log_path="${EP_PATH}/openblas_cmake.log"
  readonly openblas_make_log_path="${EP_PATH}/openblas_make.log"
  readonly openblas_make_install_log_path="${EP_PATH}/openblas_make_install.log"
  rm -f "${exprtk_wget_log_path}"  
  rm -f "${boost_wget_log_path}"
  rm -f "${boost_boostrap_log_path}"
  rm -f "${boost_bjam_log_path}"
  rm -f "${lapack_wget_log_path}"
  rm -f "${lapack_cmake_log_path}"
  rm -f "${lapack_make_log_path}"
  rm -f "${lapack_make_install_log_path}"
  rm -f "${armadillo_wget_log_path}"
  rm -f "${armadillo_cmake_log_path}"
  rm -f "${armadillo_make_log_path}"
  rm -f "${armadillo_make_install_log_path}"
  rm -f "${openblas_wget_log_path}"
  rm -f "${openblas_cmake_log_path}"
  rm -f "${openblas_make_log_path}"
  rm -f "${openblas_make_install_log_path}"
}

#################################################################

function download_exprtk() {
  DOWNLOAD_URL="https://github.com/ArashPartow/exprtk/archive/master.zip"
  cd "${EP_PATH}"
  [ -f "exprtk.zip" ] || wget -O exprtk.zip "${DOWNLOAD_URL}" |& tee "${exprtk_wget_log_path}"
  #mv master.zip exprtk.zip
  rm exprtk-master
  unzip exprtk.zip
  cd exprtk-master
  cp exprtk.hpp "${EP_PATH}/include/"
  cd "${EP_PATH}"
  rm -rf exprtk-master
}

#################################################################

function download_and_build_boost() {
  BOOST_VERSION='1.68.0'
  BOOST="boost_${BOOST_VERSION//./_}"
  DOWNLOAD_URL="http://downloads.sourceforge.net/project/boost/boost/${BOOST_VERSION}/${BOOST}.tar.gz"
  cd "${EP_PATH}"
  [ -f "${BOOST}.tar.gz" ] || wget "${DOWNLOAD_URL}" |& tee "${boost_wget_log_path}"
  rm -rf ${BOOST}
  tar xzf ${BOOST}.tar.gz
  cd ${BOOST}
  ./bootstrap.sh |& tee "${boost_boostrap_log_path}"
  ./bjam link=static \
         --toolset=gcc\
         --cxxflags="-std=c++17"\
         --layout=system\
         --build-type=minimal\
         --with-program_options\
         --with-system\
         --prefix=${EP_PATH}\
         install |& tee "${boost_bjam_log_path}" 
  cd ${EP_PATH}
  rm -rf ${BOOST}
}

#################################################################

function download_and_build_lapack() {
  LAPACK='lapack-3.8.0'
  DOWNLOAD_URL="http://www.netlib.org/lapack/${LAPACK}.tar.gz"
  cd "${EP_PATH}"
  [ -f "${LAPACK}.tar.gz" ] || wget "${DOWNLOAD_URL}" |& tee "${lapack_wget_log_path}"
  rm -rf "${LAPACK}"
  tar zxvf "${LAPACK}.tar.gz"
  cd ${LAPACK}
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX:PATH=${EP_PATH} \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DCMAKE_PREFIX_PATH:PATH=${EP_PATH} \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        ..  |& tee "${lapack_cmake_log_path}"
  make -j "${jobs}" |& tee "${lapack_make_log_path}"
  make install |& tee "${lapack_make_install_log_path}"
  cd "${EP_PATH}"
  rm -rf "${LAPACK}"
}

################################################################

function download_and_build_armadillo() {
  ARMADILLO='armadillo-9.100.5'
  DOWNLOAD_URL="https://downloads.sourceforge.net/project/arma/${ARMADILLO}.tar.xz"
  [ -f "${ARMADILLO}.tar.xz" ] || wget "${DOWNLOAD_URL}" |& tee '${armadillo_wget_log_path}'
  rm -rf "${ARMADILLO}"
  tar xvf "${ARMADILLO}.tar.xz"
  cd "${ARMADILLO}"
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX:PATH=${EP_PATH} \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DCMAKE_PREFIX_PATH:PATH=${EP_PATH} \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        .. |& tee "${armadillo_cmake_log_path}"
  make -j "${jobs}" all |& tee "${armadillo_make_log_path}"
  make install |& tee "${armadillo_make_install_log_path}"
  cd "${EP_PATH}"
  rm -rf "${ARMADILLO}"
}

################################################################

function download_and_build_openblas() {
  OPENBLAS_VERSION=0.3.3
  OPENBLAS=OpenBLAS-${OPENBLAS_VERSION}
  DOWNLOAD_URL="http://github.com/xianyi/OpenBLAS/archive/v${OPENBLAS_VERSION}.tar.gz"
  [ -f ${OPENBLAS}.tar.gz ] || wget "${DOWNLOAD_URL}" |& tee "${openblas_wget_log_path}"
  mv v${OPENBLAS_VERSION}.tar.gz ${OPENBLAS}.tar.gz
  tar xf "${OPENBLAS}.tar.gz"
  cd "${OPENBLAS}"
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX:PATH=${EP_PATH} \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DBUILD_SHARED_LIBS=Off \
        -DDYNAMIC_ARCH=On \
        -DUSE_THREAD=Off \
        .. |& tee "${openblas_cmake_log_path}"
  make -j ${jobs} all |& tee "${openblas_make_log_path}"
  make install |& tee "${openblas_make_install_log_path}"
  cd "${EP_PATH}"
  rm -rf "${OPENBLAS}"
}

#####################################
###### MAIN #########################
#####################################

init
download_and_build_boost
download_and_build_openblas
download_and_build_lapack
download_and_build_armadillo

