#PAF recompilation forced and copy here.
cd ../build/
make clean
make -j8
cp libPAF.so ../sandbox/
#Copy headers except *LinkDefs to allow packages compilation.
cd ../src/
mkdir -p ./.paf/BuildDir/packages/PAF
find . -name '*.h' ! -name '*LinkDef.h' | cpio -pdm ../sandbox/.paf/BuildDir/packages/PAF
#Back to sandbox directory.
cd ../sandbox/
root -l
#Should launch now a "gSystem->Load("libPAF.so").
