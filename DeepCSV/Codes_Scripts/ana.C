#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//#include "RHAna.h"
/*
This is a driver script.
It decides which code to run over which sample, the names
of output files and so on.
*/


void ana(int sample=1)
{
  const char *hstfilename, *sumfilename;
  //Declare a chain for input files.
  TChain *chain = new TChain("Events");
  //Declare an instance of our code class
  VLLAna m_selec;
  
  if(sample==1){
    //Add one file to chain. This is the input file.
    chain->Add("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/NanoPost_TTToSemiLeptonic_TuneCP5_99.root");
    //Set names of output files.
    hstfilename = "hst_TTBar.root";
    sumfilename = "sum_TTBar.txt";
    //Set some options.. data is 0 since this input file is simulation.
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
  }
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<std::endl;
  // Set some more options.. set the output file names.
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(10);//set verbosity level for output.
  // Call the process function which runs the code.
  chain->Process(&m_selec);
}
