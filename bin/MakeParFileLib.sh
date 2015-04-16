#!/bin/bash

####################################################################
#     FILE: MakeParFileLib.sh
# AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero, 
#          J. Delgado Fernández
#    DATE: 2015
#
# CONTENT: Makes .par files for a given library 
#          Use MakeParFileLib.sh -help for more information
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
	`basename $0`: This script creates the .par file for a given library PAR 
			files used by PROOF to transfer the code to the slaves.

SYNTAX: 
	`basename $0` [--help] [-s|--silent] packagename

OPTIONS:
	-h, --help
		Shows this help
	-s, --silent
		Do not print output (by default it is printed)
	-v, --verbose
		Include debug output when making the packages
	-d, --dest path
		Create packages at specified path (default: .)
	librarypath
		The path to the library. It is mandatory.
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
# Create the par file in $1 for package $3 which is located in $2
createparfile() {
	if [ -f $basepath/$parpackagename ]; then
		if [ $silent -ne 0 ]; then
			myecho "Moving $basepath/$parpackagename to $basepath/$parpackagename.bak"
		fi
		mv $basepath/$parpackagename $basepath/$parpackagename.bak
	fi
    
	local template=$templatedir/"SETUPLib.C.in"
	mkdir --parents $destpath/PROOF-INF/
	cp -r $packagename $destpath
	cat $template \
		| sed -e "s/%NAME%/$filename/g" > $destpath/PROOF-INF/SETUP.C

	verbose=""
	if [ $debugoutput -ne 0 ] ; then
		verbose="-v"
	fi
	# XXX Be aware of any missing files in this list (--exclude CVS does not work on Mac)
	tar $verbose -czf $basepath/$parpackagename -C $basepath $filenamewe
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

filename=$(basename $packagename)
filenamewe="${filename%.*}"
parpackagename=$filenamewe.par
templatedir=`dirname $0`/../etc


myecho "Silent = $silent"
myecho "Debug = $debugoutput"
myecho "Package Name = $packagename"
myecho "Package Par file = $parpackagename"
myecho "Package dest = $basepath"

destpath=$basepath$filenamewe

createparfile $basepath $parpackagename
sync
