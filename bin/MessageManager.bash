#!/bin/bash
#

# bash script to start Message Manager with dragonfly library in source location
#

echo ""
# get folder where tools are located
BIN_DIR=`dirname $0`
BIN_DIR=`cd ${BIN_DIR}; pwd; cd - 1>/dev/null`
echo "Dragonfly bin folder : ${BIN_DIR}"

# find library folder
LIB_DIR=`cd ${BIN_DIR}/../lib; pwd; cd - 1>/dev/null`
echo "Dragonfly lib folder : ${LIB_DIR}"

# starting message manager
CMD="LD_LIBRARY_PATH=${LIB_DIR} ${BIN_DIR}/MessageManager"
echo "Starting Message Manager with command =>${CMD}<="
echo "-------------------------------------"
echo ""
LD_LIBRARY_PATH=${LIB_DIR} ${BIN_DIR}/MessageManager

