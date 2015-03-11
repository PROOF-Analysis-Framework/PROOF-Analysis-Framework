#!/bin/bash

THIS=$(dirname ${BASH_ARGV[0]})
PAFPATH=$(cd ${THIS};pwd); export PAFPATH


export PATH=$PATH:$PAFPATH/bin
export PAFREPOSITORIES=~/Documents/PROOF-Analysis-Framework/sandbox/packages
source /opt/root/bin/thisroot.sh
