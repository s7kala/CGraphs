#!/bin/bash

# path variables

INSTALL_PATH=${PWD}
SOURCE_PATH=${INSTALL_PATH}/source
RELEASE_PATH=${INSTALL_PATH}/lib

INCLUDES=graph.h

# prepare library and move to release

cd ${SOURCE_PATH} && 
make release && 
cp ${INCLUDES} ${RELEASE_PATH}/include
cp *.o ${RELEASE_PATH} &&
make clean
