#!/bin/bash

####################################################################
#     FILE: CompileLibrary.sh
# AUTHORS: I. Gonzalez Caballero, J. Delgado Fernández
#    DATE: 2015-01-24
#
# CONTENT: Compile the specified package.
#          Use CompileLibrary.sh -help for more information
####################################################################


####################################################################
# Default values of some variables
silent=0
setup=1
debugoutput=0
isremote=0
basepath="."

####################################################################
# Print some information on how to use this script
usage() {
    cat << EOF
`basename $0`: This script compile a package already created to so object.

SYNTAX: 
  `basename $0` [--help] [-s|--silent] [-n|--nosetup] [-r|--remote path] packagename

OPTIONS:
  -h, --help
       Shows this help

  -s, --silent
       Do not print output (by default it is printed)


  -v, --verbose
       Include debug output when making the packages


  -d, --dest path
       Create packages at specified path (default: .)

  packagename
       The name of the package. It is mandatory

EOF
}

######################################################################
# Helper functions to show information and errors
myecho() {
    if [ $silent -eq 0 ]; then
	echo "PAF [I] $*"
    fi
}

myerror() {
    echo -e -n "\033[1;31mPAF [E] " $* 1>&2
    echo -e "\033[0m" 1>&2
}


######################################################################
# Compile specified package in -d destination.
compilepackage() {
    myecho ">> Creating $parpackagename for package in $basepath..."

    if [ ! -d $destpath/PROOF-INF -o ! -e $destpath/PROOF-INF/SETUP.C ] ; then
	    myerror "Could not find PROOF package files"
    	myerror "$packagedir is not a PROOF package. Exiting!"
    fi

    if [ -f $basepath/$parpackagename ]; then
        if [ $silent -ne 0 ]; then
            myecho "Moving $basepath/$parpackagename to $basepath/$parpackagename.bak"
        fi
        mv $basepath/$parpackagename $basepath/$parpackagename.bak
    fi

    verbose=""
    if [ $debugoutput -ne 0 ] ; then
        verbose="-v"
    fi
    # XXX Be aware of any missing files in this list (--exclude CVS does not work on Mac)
    #tar $verbose -c -z -f $basepath/$parpackagename -C $basepath $packagename
    echo $basepath$packagename
	cd $basepath$packagename
	make
}


######################################################################
# Process command line
if [ -z $1 ]; then
    usage
    exit
fi

while [ "$1" != "" ]; do
    case $1 in
        -s | --silent )
            silent=1
            ;;
        -v|--verbose)
            debugoutput=1
            ;;
        -d|--dest)
            shift
            basepath=$1
            ;;
        -h | --help )
            usage
            exit
            ;;
        * )
            packagename=$1
    esac
    shift
done

origppath=packages/$packagename
packagelibname=$packagename

myecho "Silent = $silent"
myecho "Setup = $setup"
myecho "Debug = $debugoutput"
myecho "Package Name = $packagename"
myecho "Package Par file = $parpackagename"
myecho "Package dest = $basepath"

destpath=$basepath/$packagename

compilepackage $basepath $parpackagename
sync
