#!/bin/bash
#

# bash script to build messages definitions files for matlab and python
# starting from .h file
#

# header file is the first input, or at least we hope so
hfile=$1

# set temporarly correct path to dragonfly
export DRAGONFLY=`cd ../..;pwd`

# get folder where tools are located
TOOLS_DIR=`cd ../../tools;pwd`

# call python script to create .py message definitions module
echo "Generating Python module..."
python ${TOOLS_DIR}/build_python_message_defs.py ${hfile} && echo "===> SUCCESS" || echo "===> FAILED"
echo "...Done"

# run matlab script to create .m message definitions file
echo "Generating Matlab file..."
${MATLAB_EXE} -nodesktop -nosplash -nojvm -r "addpath('${TOOLS_DIR}'); build_matlab_message_defs('${hfile}'); exit;" && echo "===> SUCCESS" || echo "===> FAILED"
echo "...Done"

