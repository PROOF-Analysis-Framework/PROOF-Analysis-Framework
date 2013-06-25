#!/bin/bash

####################################################################
#    FILE: checkversion.sh
# AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
#    DATE: 01/02/2011
#
# CONTENT: Checks if the PAF installation is up to date by comparing
#          the version written in README with the latest version in
#          published.
#
#          Obsolete after moving to GIT
####################################################################

findwebversion() {
    webfile=`mktemp`
    
    wget -q http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/IFCA-UO/PAF/ -O $webfile 2&> /dev/null
    
    latestversion=`grep -A 3 Non-branch $webfile | grep option | cut -d \> -f 2 | cut -d \< -f 1`
    rm $webfile
}

findlocalversion() {
    currentversion=`grep \\$Name $PAFPATH/README| sed 's/\\$//g' | cut -d: -f 2  | sed 's/ //g'`
}

if [ ! -f $PAFPATH/README ]; then
    echo "NOTE: Could not find README file to check updates"
    exit
fi

findlocalversion
if [ "$currentversion" == "" ]; then
    #If we are here is because we are not using a tagged version of PAF
    #echo "DEBUG: No tag"
    exit
fi

findwebversion
if [ "$latestversion" != "$currentversion" ]; then
    echo -e "\033[0;33mNOTE: You are not using the latest version of PAF in CVS (\033[1;33m$latestversion\033[0;33m)"
    echo -e "      Your current version is \033[1;33m$currentversion\033[0;33m. Please consider updating!"
    echo -e "      For a detailed list of improvements see:"
    echo -e "      http://www.hep.uniovi.es/mediawiki-1.12.0/index.php/ProofAnalysisFramework#$latestversion\033[0m"
fi
 
