/*========================================================
  Macro for ChainedSelectorWithVectors project.
  
  DESCRIPTION:
  This is the main macro of an example on how to build
  chained selectors that pass information among then using
  objects of non basic types.

  The project has 2 selectors:
  * SelA creates a TLorentzVector and an std::vector of
    TLorentzVector's
  * SelB finds the parameters passed and checks they are
    the same as those passed by SelA

  The main addition is the file LinkDef.h file in 
  packages/SelA. 

  Some more information in the PAF tutorials "4 Parameter passing":
  http://www.hep.uniovi.es/PAF/home/tutorials/4-parameter-passing/

  ========================================================*/

void ChainedSelectorWithVectors() {

  // (1) Create the PAF project. 
  //     By default this would the PROOF Lite environment
  //     Other options:
  //     + Sequential:    new PAFProject(new PAFSequentialEnvironment())
  //     + PROOF Lite:    new PAFProject(new PAFPROOFLiteEnvironment())
  //     + PoD:           new PAFProject(new PAFPoDEnvironment(20))
  //     + PROOF Cluster: new PAFProject(new PAFPROOFClusterEnvironment())
  //     + PROOF Cloud:   new PAFProject(new PAFPROOFCloudEnvironment())
  PAFProject* myProject = new PAFProject(new PAFPROOFLiteEnvironment());
  

  // (2) Define the data files to be used.
  //     Select the files to be analysed and replicate the
  //     line below as needed
  myProject->AddDataFile("You have to specify the input file");

  
  // (3) Define the name of the selector to be used.
  //     In this case we define two selectors: SelA & SelB.
  //     They can be found in the folder "packages"
  //
  //     Modify the line below to specify the name of your selector
  //     To create a new selector you may use PAF tools:
  //     $ paf createselector SelectorName
  myProject->AddSelectorPackage("SelA");
  myProject->AddSelectorPackage("SelB");
  
  // (4) Run the project. 
  //     This will start the processing
  myProject->Run();
}
