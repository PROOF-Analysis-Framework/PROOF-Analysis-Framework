#!/bin/bash

####################################################################
#     FILE: MakeParFile.sh
# AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
#    DATE: 2010
#
# CONTENT: Makes .par files for a given package 
#          Use MakeParFile.sh -help for more information
####################################################################


####################################################################
# Default values of some variables
silent=0
setup=1
forcesetup=0
ispackagename=0
debugoutput=0
isremote=0
remotepath=""
basepath="."

####################################################################
# Print some information on how to use this script
usage() {
    cat << EOF
`basename $0`: This script creates the .par file for a given package. Par 
                files used by PROOF to transfer the code to the slaves.

SYNTAX: 
  `basename $0` [--help] [-s|--silent] [-n|--nosetup] [-r|--remote path] packagename

OPTIONS:
  -h, --help
       Shows this help

  -s, --silent
       Do not print output (by default it is printed)

  XXX: WHAT?
  -n, --nosetup
       Do not try to create PROOF-INF/SETUP.C file. By default it will be
       created if it is not found.

  -f, --forcesetup
       Recreate PROOF-INF/SETUP.C,  PROOF-INF/BUILD.sh and Makefile. 
       By default if it exists it will not be recreated. It is incompatible
       with the option --nosetup

  -v, --verbose
       Include debug output when making the packages

  -r, --remote path
       Get package from specified path

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
# Creates file from template
writefromtemplatefile() {
    local file=$1
    local template=$templatedir/`basename $1`.in
    myecho ">> Writting $file for $packagename in $destpath"

    local d=$destpath/`dirname $file`
    if [ ! -d $d ] ; then
        myecho "   + $d does not exist. Creating it"
        mkdir -p $d
    fi

    cat $template \
        | sed -e "s/%NAME%/$packagelibname/g" \
        | sed -e "s/%VERBOSE%/$debugoutput/g" > $destpath/$file
}

######################################################################
# This function makes the PROOF-INF/SETUP.C file
writesetup() {
    writefromtemplatefile PROOF-INF/SETUP.C
}

######################################################################
# This function makes the PROOF-INF/BUILD.sh file
writebuildsh() {
    writefromtemplatefile PROOF-INF/BUILD.sh
    chmod u+x $destpath/PROOF-INF/BUILD.sh
}

######################################################################
# This function makes the Makefile file
writemakefile() {
    if [ -f $ROOTSYS/etc/Makefile.arch ] ; then
        cp $ROOTSYS/etc/Makefile.arch $destpath/Makefile.arch
    elif [ -f $ROOTSYS/test/Makefile.arch ] ; then
        cp $ROOTSYS/test/Makefile.arch $destpath/Makefile.arch
    elif [ -f $ROOTSYS/share/doc/root/test/Makefile.arch ] ; then
        cp $ROOTSYS/share/doc/root/test/Makefile.arch $destpath/Makefile.arch
    fi
    writefromtemplatefile Makefile
}

######################################################################
# Create the par file in $1 for package $3 which is located in $2
createparfile() {
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
    tar $verbose -c -z -f $basepath/$parpackagename -C $basepath $packagename
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
        -n | --nosetup )
            setup=0
            ;;
        -f|--forcesetup )
            forcesetup=1
            ;;
        -r|--remote )
            shift
            remotepath=$1
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

if [ $forcesetup -eq 1 -a $setup -eq 0 ]; then
    myerror "--nosetup and --forcesetup are incompatible"
    exit 1
fi

if [ "x$packagename" = "x" ]; then
    myerror "No package name specified"
    exit 1
fi

if [ "x$remotepath" != "x" ]; then
    if [ -d $remotepath/$packagename ] ; then
        packagedir=$remotepath/$packagename
    else
        myerror "Unable to find $packagename at $remotepath"
        exit 1
    fi
else
    if [ -d packages/$packagename ] ; then
        packagedir=packages/$packagename
    elif [ -d $PAFPATH/packages/$packagename ] ; then
        packagedir=$PAFPATH/packages/$packagename
    else
        myerror "Unable to find any package named $packagename"
        exit 1
    fi
fi

parpackagename=$packagename.par
origppath=packages/$packagename
templatedir=`dirname $0`/../etc
packagelibname=$packagename

myecho "Silent = $silent"
myecho "Setup = $setup"
myecho "Force = $forcesetup"
myecho "Debug = $debugoutput"
myecho "Package Name = $packagename"
myecho "Package Par file = $parpackagename"
myecho "Package orig = $packagedir"
myecho "Package dest = $basepath"

destpath=$basepath/$packagename

if [ $destpath == $packagedir ] ; then
    myerror "Destination and origin are the same! not doing anything."
    exit 1
fi
    
if [ -d $destpath ] ; then
    rm -rf $destpath
fi

myecho "Copying $packagedir to $basepath"
cp -r $packagedir $basepath

# Check whether we need to create the SETUP.C file
if [ $setup -eq 1 ]; then
    if [ ! -e $destpath/PROOF-INF/SETUP.C ]; then
        forcesetup=1
    fi
    if [ ! -e $destpath/PROOF-INF/BUILD.sh ]; then
        forcesetup=1
    fi
    if [ ! -e $destpath/Makefile -o ! -e $destpath/Makefile.arch ]; then
        forcesetup=1
    fi
fi

myecho "Force setup is $forcesetup"

# Figure out if the library is called just like the pkg or not
# XXX assume only one .C file there
if [ ! -f $destpath/$packagename.C ]; then
    cfilename=`ls $destpath/*.C | head -1 | sed "s/\.C$//"`
    packagelibname=`basename $cfilename`
fi

if [ $forcesetup -eq 1 ]; then
    writesetup 
    writebuildsh
    writemakefile 
fi
createparfile $basepath $parpackagename
