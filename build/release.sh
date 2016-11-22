#!/bin/sh
d=${PWD}
bd=${d}/../
id=${bd}/install
ed=${d}/../
rd=${d}/../reference/
d=${PWD}
is_debug="n"
build_dir="build_unix"
cmake_build_type="Release"
cmake_config="Release"
debug_flag=""
debugger=""
cmake_generator=""

# Detect OS.
if [ "$(uname)" == "Darwin" ]; then
    if [ "${cmake_generator}" = "" ] ; then
        cmake_generator="Unix Makefiles"
        compiler="clang"
    fi
    os="mac"
    debugger="lldb"
elif [ "$(expr substr $(uname -s) 1 5)" = "Linux" ]; then
    if [ "${cmake_generator}" = "" ] ; then
        cmake_generator="Unix Makefiles"
        compiler="gcc"
    fi
    os="linux"
    debugger="gdb"
else
    if [ "${cmake_generator}" = "" ] ; then
        cmake_generator="Visual Studio 14 2015 Win64"
        build_dir="build_vs2015"
        compiler="vs2015"
    fi
    os="win"
fi

# Detect Command Line Options
for var in "$@"
do
    if [ "${var}" = "debug" ] ; then
        is_debug="y"
        cmake_build_type="Debug"
        cmake_config="Debug"
        debug_flag="_debug"
    elif [ "${var}" = "xcode" ] ; then
        build_dir="build_xcode"
        cmake_generator="Xcode"
        build_dir="build_xcode"
        compiler="xcode"
    elif [ "${var}" = "vs2013" ] ; then
        build_dir="build_vs2013"
        compiler="vs2013"
        debugger=""
        cmake_generator="Visual Studio 12 2013 Win64"
    fi
done

install_dir="${id}/${compiler}${debug_flag}"

# Create unique name for this build type.
bd="${d}/${build_dir}.${cmake_build_type}"

if [ ! -d ${bd} ] ; then 
    mkdir ${bd}
fi

# Compile the library.
cd ${bd}

cmake -DCMAKE_INSTALL_PREFIX=${install_dir} \
      -DCMAKE_BUILD_TYPE=${cmake_build_type} \
      -G "${cmake_generator}" \
      ..

if [ $? -ne 0 ] ; then
    exit
fi

cmake --build . --config ${cmake_build_type} --target install

if [ $? -ne 0 ] ; then
    exit
fi

cd ${install_dir}/bin
${debugger} ./remoxly_example
