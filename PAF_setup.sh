#!/bin/bash
if [ ! -n "${ROOTSYS}" ] ; then
    echo "WARNING: ROOT environment is not set."
    echo "         Please source /opt/root/bin/thisroot.sh"
fi


THIS=$(dirname ${BASH_ARGV[0]})
PAFPATH=$(cd ${THIS};pwd); export PAFPATH


export PATH=$PATH:$PAFPATH/bin
