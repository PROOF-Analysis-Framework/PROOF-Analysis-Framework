/*========================================================
  Macro for RunBasicSelector project.
  
  DESCRIPTION:
  This is the main macro of an example on how to build
  a very simple and basic selector.

  See the tutorials for more information.

  ========================================================*/

void RunBasicSelector() {
  // (1) Create the PAF project. 
  //     By default this would the PROOF Lite environment
  //     Other options:
  //     + Sequential:    new PAFProject(new PAFSequentialEnvironment())
  //     + PROOF Lite:    new PAFProject(new PAFPROOFLiteEnvironment())
  //     + PoD:           new PAFProject(new PAFPoDEnvironment(20))
  //     + PROOF Cluster: new PAFProject(new PAFPROOFClusterEnvironment())
  //     + PROOF Cloud:   new PAFProject(new PAFPROOFCloudEnvironment())
  PAFProject* myProject = new PAFProject();


  // (2) Define the data files to be used.
  //     Select the files to be analysed and replicate the
  //     line below as needed
  myProject->AddDataFile("/path/to/file.root");


  // (3) Define the name of the selector to be used.
  //     In this case it is BasicSelector and it is defined
  //     in the folder packages/BasicSelector
  //
  //     Modify the line below to specify the name of your selector
  //     To create a new selector you may use PAF tools:
  //     $ paf createselector SelectorName
  myProject->AddSelectorPackage("BasicSelector");


  // (4) Run the project. 
  //     This will start the processing
  myProject->Run();
}
