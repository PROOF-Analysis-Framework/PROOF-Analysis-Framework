#!/bin/bash

# Configuration of PAFPATH guess from the current location of this script
THIS=$(dirname ${BASH_ARGV[0]})
PAFPATH=$(cd ${THIS};pwd); export PAFPATH

# Colon separated list of paths where modules and packages are to be looked for
export PAFREPOSITORIES=$(pwd)/sandbox/packages

# Add PAFPATH/bin to PATH
export PATH=$PATH:$PAFPATH/bin

# Add PAF lib path to libraries that ROOT should find.
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PAFPATH/lib

if [ -z $ROOTSYS ]; then
  echo "WARNING: It seems you have not configured your ROOT environment"
  echo "         This is usually done with 'source /opt/root/bin/thisroot.sh'"
fi

if [  ! -z $1 ]; then
  if [ "$1" == "-v" ]; then
     echo "PAF has been configured correctly:"
     echo "+ PAF is installed in $PAFPATH"
     echo "+ PAF Repositories are set to $PAFREPOSITORIES"
  fi
fi
