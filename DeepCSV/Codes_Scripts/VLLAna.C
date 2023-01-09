#define VLLAna_cxx
// The class definition in VLLAna.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("VLLAna.C")
// root> T->Process("VLLAna.C","some options")
// root> T->Process("VLLAna.C+")
//


#include "VLLAna.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <iostream>
#include <iomanip>
#include "JetEffFunction.h"

void VLLAna::Begin(TTree * /*tree*/)
{
     // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   nEvtTotal          =0;
   nEvtRan            =0;
   //VLL 
   n_2L    =0;
   n_1L1Tau=0;
   n_1L2J  =0;
     
   //Create the histogram file
   _HstFile = new TFile(_HstFileName,"recreate");
   //Call the function to book the histograms we declared in Hists.
   BookHistograms();
   }

void VLLAna::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t VLLAna::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  fReader.SetLocalEntry(entry);
  
  if(_verbosity==0 && nEvtTotal%1000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%100000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;

  
  nEvtTotal++;
  h.nevt[0]->Fill(0);

  h.metfilter[0]->Fill(*Flag_goodVertices);
  h.metfilter[1]->Fill(*Flag_globalSuperTightHalo2016Filter);
  h.metfilter[2]->Fill(*Flag_HBHENoiseFilter);
  h.metfilter[3]->Fill(*Flag_HBHENoiseIsoFilter);
  h.metfilter[4]->Fill(*Flag_EcalDeadCellTriggerPrimitiveFilter);
  h.metfilter[5]->Fill(*Flag_BadPFMuonFilter);
  h.metfilter[6]->Fill(*Flag_eeBadScFilter);
  
  GoodEvt2018 = (_year==2018 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2017 = (_year==2017 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2016 = (_year==2016 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  
  h.metfilter[7]->Fill(GoodEvt2016);
  h.metfilter[8]->Fill(GoodEvt2017);
  h.metfilter[9]->Fill(GoodEvt2018);
  
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016;
  
  h.metfilter[10]->Fill(GoodEvt);
  
  if(GoodEvt){
    
    nEvtRan++;
    Genllep.clear();
    llep.clear();
    loosellep.clear();
    
    /********************************************************************************
     *                                GenElectrons                                  *
     ********************************************************************************/
    GenEle.clear();
    for(UInt_t i=0; i<*nGenPart; i++){
      Lepton temp;
      temp.v.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
      temp.ind=i;
      temp.id=GenPart_pdgId[i];
      temp.momid= GenMother(i, GenPart_genPartIdxMother[i]);
      temp.status= GenPart_status[i];
      
      bool passCuts = temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
      if(fabs(temp.id) == 11 && temp.status==1 && passCuts){ 
	h.mom[0]->Fill(temp.momid);
	GenEle.push_back(temp);
	Genllep.push_back(temp);
	
      }
    }
    
    h.genele[0]->Fill((int)GenEle.size());
    for(int j=0 ; j<(int)GenEle.size(); j++){
      h.genele[1]->Fill(GenEle.at(j).v.Pt());
      h.genele[2]->Fill(GenEle.at(j).v.Eta());
      h.genele[3]->Fill(GenEle.at(j).v.Phi());
    }
    
    /********************************************************************************
     *                                GenMuons                                      *
     ********************************************************************************/
    GenMu.clear();
    
    for(UInt_t i=0; i<*nGenPart; i++){
      Lepton temp;
      temp.v.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
      temp.ind=i;
      temp.id=GenPart_pdgId[i];
      temp.momid= GenMother(i, GenPart_genPartIdxMother[i]);
      temp.status= GenPart_status[i];
      
      bool passCuts = temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
      if(fabs(temp.id) == 13 && temp.status==1 && passCuts){ 
	h.mom[1]->Fill(temp.momid);
	GenMu.push_back(temp);
	Genllep.push_back(temp);
      }
    } 
    
    h.genmu[0] ->Fill((int)GenMu.size());
    h.genllep[0]->Fill((int)Genllep.size());
    for(int j=0 ; j<(int)GenMu.size(); j++){
      h.genmu[1]->Fill(GenMu.at(j).v.Pt());
      h.genmu[2]->Fill(GenMu.at(j).v.Eta());
      h.genmu[3]->Fill(GenMu.at(j).v.Phi());
    }
    
    /********************************************************************************
     *                                GenTaus                                       *
     ********************************************************************************/
    GenTaus.clear();
    
    for(UInt_t i=0; i<*nGenPart; i++){
      Lepton temp;
      temp.v.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
      temp.ind=i;
      temp.momid= GenMother(i, GenPart_genPartIdxMother[i]);
      temp.id=GenPart_pdgId[i];
      
      temp.status= GenPart_status[i];
      bool passCuts = temp.v.Pt()>5 && fabs(temp.v.Eta())<2.3 && fabs(temp.momid) != 22 && fabs(temp.momid)<100;
      
      if(fabs(temp.id) == 15 && passCuts){
	h.mom[2]->Fill(temp.momid);
	GenTaus.push_back(temp);
      }
    }
    
    h.gentau[0]->Fill((int)GenTaus.size());
    for(int j=0 ; j<(int)GenTaus.size(); j++){
      h.gentau[1]->Fill(GenTaus.at(j).v.Pt());
      h.gentau[2]->Fill(GenTaus.at(j).v.Eta());
      h.gentau[3]->Fill(GenTaus.at(j).v.Phi());
    }
    
    
    /********************************************************************************
     *                                 Muons                                        *
     ********************************************************************************/
    tempGoodMu.clear();
    GoodMu.clear();
    looseMu.clear();//Creating loose Muon array to clean taus/Jets from loose muons
    
    for(unsigned int i=0; i<(*nMuon); i++){
      Lepton temp;
      temp.v.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],0.105);
      temp.id = -13*Muon_charge[i];
      temp.ind = i;
      temp.charge = Muon_charge[i];
      temp.dz=Muon_dz[i];
      temp.dxy=Muon_dxy[i];
      
      //Creating loosemuon array
      bool passcut_loosemuon = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Muon_pfRelIso04_all[i]<0.30 && Muon_looseId[i];
      if(passcut_loosemuon){
	loosellep.push_back(temp);
	looseMu.push_back(temp);
      }
      
      //Creating medium muon array
      bool passCuts = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Muon_pfRelIso04_all[i]<0.15;
      passCuts = passCuts && fabs(temp.dxy)<0.05 && fabs(temp.dz)<0.1 && Muon_mediumId[i];
      
      //dR matching muons with GenMuons
      /*      float dR_Mu_GenMu = 999.0;
      for(int j=0; j<(int)GenMu.size(); j++){
	float dR_value= temp.v.DeltaR(GenMu.at(j).v);
	if(dR_value<dR_Mu_GenMu){
	  dR_Mu_GenMu=dR_value;
	}
      }
      
      h.dR[0]->Fill(dR_Mu_GenMu);*/
      
      if(passCuts){// && dR_Mu_GenMu<0.1 ){
	tempGoodMu.push_back(temp);
      }
      
      //cutFlow(Debugging)
      if(temp.v.Pt()>10){//pt
	h.mucut->Fill(0);
	if(fabs(temp.v.Eta())<2.4){//eta
	  h.mucut->Fill(1);
	  if(fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1){//dxydz
	    h.mucut->Fill(2);
	    if(Muon_pfRelIso04_all[i]<0.30 && Muon_looseId[i]){//loose
	      h.mucut->Fill(3);
	      if(Muon_mediumId[i]){//medium
		h.mucut->Fill(4);
		if(Muon_pfRelIso04_all[i]<0.15){//PFIso
		  h.mucut->Fill(5);
		}
	      }	    
	    }
	  }
	}
      }
      
    }
    
    SortPt(0);
    
    //Each muon should be 0.2 dR away from every other muon
    if((int)tempGoodMu.size()>0){
      GoodMu.push_back(tempGoodMu.at(0));
      llep.push_back(tempGoodMu.at(0));
      for(int i=1; i<(int)tempGoodMu.size(); i++) {
	bool isanyclose = false;
	for(int j=0; j<(int)GoodMu.size(); j++){
	  if(tempGoodMu.at(i).v.DeltaR(GoodMu.at(j).v)<0.2)
	    isanyclose = true;
	}
	
	if(!isanyclose){
	  GoodMu.push_back(tempGoodMu.at(i));
	  llep.push_back(tempGoodMu.at(i));
	}
      }
    }
    SortPt(1);
    
    //Muon Array
    h.muons[0]->Fill((int)GoodMu.size());
    for(int i=0; i<(int)GoodMu.size(); i++){
      h.muons[1]->Fill(GoodMu.at(i).v.Pt());
      h.muons[2]->Fill(GoodMu.at(i).v.Eta());
      h.muons[3]->Fill(GoodMu.at(i).v.Phi());
    }
    
    /********************************************************************************
     *                               Electrons                                      *
     ********************************************************************************/
    tempGoodEle.clear();
    GoodEle.clear();
    looseEle.clear();//Creating loose electron array to clean jets/taus of the loose electrons
    
    for(unsigned int i=0; i<(*nElectron); i++){
      Lepton temp;
      temp.v.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],0.000511); 
      temp.id = -11*Electron_charge[i];
      temp.ind = i;
      temp.charge = Electron_charge[i];
      temp.dz=Electron_dz[i];
      temp.dxy=Electron_dxy[i];
      
      bool passcut_looseEle = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Electron_cutBased[i]>1; //Loose electron
      if(passcut_looseEle){
	loosellep.push_back(temp);
	looseEle.push_back(temp);
      }
      
      bool isprompt = false;
      if(fabs(temp.v.Eta())<=1.479)
	if(fabs(temp.dxy)<0.05 && fabs(temp.dz)<0.1)
	  isprompt = true;      
      if(fabs(temp.v.Eta())>1.479)
	if(fabs(temp.dxy)<0.1 && fabs(temp.dz)<0.2)
	  isprompt = true;
      
      bool passCuts = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Electron_cutBased[i]>2;
      passCuts = passCuts && isprompt;
      
      //dR matching with GenElectrons
      /*float dR_Ele_GenEle = 999.0;
	for(int j=0; j<(int)GenEle.size(); j++){
	float dR_value= temp.v.DeltaR(GenEle.at(j).v);
	if(dR_value<dR_Ele_GenEle){
	dR_Ele_GenEle=dR_value;
	}
	}
	h.dR[1]->Fill(dR_Ele_GenEle);
	passCuts = passCuts && dR_Ele_GenEle<0.1;*/
      
      //Each electron should be 0.2 dR away from every muon
      bool ismuonclose = false;
      for(int k=0; k<(int)GoodMu.size(); k++){
	if(temp.v.DeltaR(GoodMu.at(k).v)<0.2){
	  ismuonclose= true;
	}
      }
      
      if(passCuts && !ismuonclose){
	tempGoodEle.push_back(temp);
      }
      
      //cutFlow(Debugging)
      if(temp.v.Pt()>10){//pt
	h.elecut->Fill(0);
	if(fabs(temp.v.Eta())<2.4){//eta
	  h.elecut->Fill(1);
	  if(isprompt){//dxydz
	    h.elecut->Fill(2);
	    if(Electron_cutBased[i]>1){//looseID
	      h.elecut->Fill(3);
	      if(Electron_cutBased[i]>2){//mediumID
		h.elecut->Fill(4);
		if(!ismuonclose){//Muon cleaning
		  h.elecut->Fill(5);
		}
	      }	    
	    }
	  }
	}
      }
      
      
    }
    SortPt(2);//Sorting tempGoodEle
    
    //Each electron should be 0.2 dR away from every other electron
    if((int)tempGoodEle.size()>0){
      GoodEle.push_back(tempGoodEle.at(0));
      llep.push_back(tempGoodEle.at(0));
      for(int i=1; i<(int)tempGoodEle.size(); i++) {
	bool isanyclose = false;
	for(int j=0; j<(int)GoodEle.size(); j++){
	  if(tempGoodEle.at(i).v.DeltaR(GoodEle.at(j).v)<0.2)
	    isanyclose = true;
	}
	if(!isanyclose){
	  GoodEle.push_back(tempGoodEle.at(i));
	  llep.push_back(tempGoodEle.at(i));
	}
      }
    }
    
    SortPt(3); //Sorting GoodEle
    SortPt(4); //Sorting llep
    
    h.electrons[0]->Fill((int)GoodEle.size());
    for(int i=0; i<(int)GoodEle.size(); i++){
      h.electrons[1]->Fill(GoodEle.at(i).v.Pt());
      h.electrons[2]->Fill(GoodEle.at(i).v.Eta());
      h.electrons[3]->Fill(GoodEle.at(i).v.Phi());
    }
    
    //Lightleptons
    h.llep[0]->Fill((int)llep.size());
    
    
    /********************************************************************************
     *                                   Taus                                       *
     ********************************************************************************/
    GoodTaus.clear();
    float tlv_corr = 1.0;
    for(unsigned int i=0; i<*nTau; i++){
      h.taucut->Fill(0);
      if(Tau_decayMode[i]&&(Tau_decayMode[i]<3||Tau_decayMode[i]>9)){
	//Tau energy scale correction
	if(_year==2016){
	  if(Tau_decayMode[i]==0) tlv_corr = 0.994;
	  if(Tau_decayMode[i]==1) tlv_corr = 0.995;
	  if(Tau_decayMode[i]>9)  tlv_corr = 1;
	}     
	if(_year==2017){
	  if(Tau_decayMode[i]==0) tlv_corr = 1.007;
	  if(Tau_decayMode[i]==1) tlv_corr = 0.998;
	  if(Tau_decayMode[i]==10) tlv_corr = 1.001;
	  if(Tau_decayMode[i]==11) tlv_corr = 0.999;
	}
	if(_year==2018){
	  if(Tau_decayMode[i]==0) tlv_corr = 0.987;
	  if(Tau_decayMode[i]==1) tlv_corr = 0.995;
	  if(Tau_decayMode[i]==10) tlv_corr = 0.998;
	  if(Tau_decayMode[i]==11) tlv_corr = 1;
	}
	
	Lepton temp; temp.v.SetPtEtaPhiM(Tau_pt[i],Tau_eta[i],Tau_phi[i],1.77);
	temp.v *= tlv_corr; //energy correction
	temp.id = -15*Tau_charge[i];
	temp.ind = i;
	temp.charge = Tau_charge[i];
	
	bool passCuts = temp.v.Pt()>20 && fabs(temp.v.Eta())<2.3;
	passCuts = passCuts && fabs(Tau_dz[i])<0.2;
	passCuts = passCuts && Tau_idDeepTau2017v2p1VSe[i] >= 15 && Tau_idDeepTau2017v2p1VSmu[i] >= 3;//loose WP
	passCuts = passCuts && Tau_idDeepTau2017v2p1VSjet[i] >= 127; //VT WP
       
	//dR matching with GenTaus
	/*float dR_Tau_GenTau = 999.0;
	  for(int j=0; j<(int)GenTaus.size(); j++){
	  float dR_value= temp.v.DeltaR(GenTaus.at(j).v);
	  if(dR_value<dR_Tau_GenTau){
	  dR_Tau_GenTau=dR_value;
	  }
	  }
	  h.dR[2]->Fill(dR_Tau_GenTau);*/
	//passCuts = passCuts && dR_Tau_GenTau<0.1;
	
	//dR cleaning for tau :
	bool isloosellepclose = false;
	for(int j=0; j<(int)loosellep.size(); j++){
	  float dR_loosellep_tau = loosellep.at(j).v.DeltaR(temp.v);
	  if(dR_loosellep_tau < 0.5)
	    isloosellepclose = true;
	}
	
	if(passCuts && !isloosellepclose){
	  GoodTaus.push_back(temp);
	}
	SortPt(5);
	
	//CutFlow(Debugging)
	h.taucut->Fill(1);//Tau Satisfying New DecayMode
	if(Tau_idDeepTau2017v2p1VSjet[i]>=127){//VT Antijet
	  h.taucut->Fill(2);
	  if(Tau_idDeepTau2017v2p1VSe[i]>=15){//Loose AntiEle
	    h.taucut->Fill(3);
	    if(Tau_idDeepTau2017v2p1VSmu[i]>=3){//Loose AntiMu
	      h.taucut->Fill(4);
	      if(fabs(Tau_dz[i]<0.2)){//Prompt Cut
		h.taucut->Fill(5);
		if(!isloosellepclose){//LooseLepton Cleaning
		  h.taucut->Fill(6);
		  if(fabs(temp.v.Eta())<2.3){// |n|<2.3 Cut
		    h.taucut->Fill(7);
		    if(temp.v.Pt()>20){//PT>20GeV Cut
		      h.taucut->Fill(8);
		    }
		  }
		}
	      }
	    }
	  }
	}
      }//Closes the if condition on the top of Tau block
    }//Close the tau loop
    
    h.taus[0]->Fill((int)GoodTaus.size());
    for(int j=0 ; j<(int)GoodTaus.size(); j++){
      h.taus[1]->Fill(GoodTaus.at(j).v.Pt());
      h.taus[2]->Fill(GoodTaus.at(j).v.Eta());
      h.taus[3]->Fill(GoodTaus.at(j).v.Phi());
    }
    
    /********************************************************************************
     *                                   Jets                                       *
     ********************************************************************************/
    GoodJets.clear();
    bTagJets.clear();
    bTagJets_MedWP.clear();
    cTagJets.clear();
    cTagJets_Mis.clear();//Mis:Mistagged
    LightTagJets.clear();
    LightTagJets_Mis.clear();

    
    for(unsigned int i=0; i<*nJet; i++){
      Lepton temp;
      temp.v.SetPtEtaPhiE(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
      temp.ind = i;
      temp.hadronflavor = Jet_hadronFlavour[i];
      bool passCuts = temp.v.Pt()>30 && fabs(temp.v.Eta())<2.4;
      
      //Anti-dR matching of Jets with loose llep
      bool isloosellepclose = false;
      for(int j=0; j<(int)loosellep.size(); j++){
	float dR_loosellep_jet = loosellep.at(j).v.DeltaR(temp.v);
	if(dR_loosellep_jet < 0.4)
	  isloosellepclose = true;
      }

      //Anti-dR matcing of Jets with Taus
      bool istauclose = false;
      for(int j=0; j<(int)GoodTaus.size(); j++){
	float dR_jet_tau = GoodTaus.at(j).v.DeltaR(temp.v);
	if(dR_jet_tau < 0.4)
	  istauclose = true;
      }
      
      if(passCuts && !isloosellepclose && !istauclose){
	if(_year == 2016 ? Jet_jetId[i]>=1 : Jet_jetId[i]>=2){
	  GoodJets.push_back(temp);
	  if(Jet_hadronFlavour[i]==5){
	    bTagJets.push_back(temp);
	    if(Jet_btagDeepB[i]>0.4168){ //bTagDiscriminator:Medium WP
	      bTagJets_MedWP.push_back(temp);
	    }
	  }
	  if(Jet_hadronFlavour[i]==4){
	    cTagJets.push_back(temp);
	    if(Jet_btagDeepB[i]>0.4168){ //bTagDiscriminator:Medium WP
	      cTagJets_Mis.push_back(temp);    
	    }
	  }
	  if(Jet_hadronFlavour[i]==0){
	    LightTagJets.push_back(temp);
	    if(Jet_btagDeepB[i]>0.4168){ //bTagDiscriminator:Medium WP
	      LightTagJets_Mis.push_back(temp);
	    }
	  }
	}
      }
    }

    float testBjetEff = 10.0;
    if((int)GoodJets.size()>0){
      testBjetEff = bTagEff2018(60,GoodJets);
      h.bTagWeight[0]->Fill(testBjetEff);
      //cout<<"The size of GoodJets array is: "<<(int)GoodJets.size()<<endl;
      //cout<<"The final bJetSF for TTBarSemiLeptonic sample is: "<<testBjetEff<<endl;
    }
    
    SortPt(6);
    h.jets[0]->Fill((int)GoodJets.size());
    for(int i=0; i<(int)GoodJets.size(); i++){
      h.jets[1]->Fill(GoodJets.at(i).v.Pt());
      h.jets[2]->Fill(GoodJets.at(i).v.Eta());
      h.jets[3]->Fill(GoodJets.at(i).v.Phi());
    }
    
    
    bool is_2l = false;
    bool is_ljj = false;
    if((int)llep.size()>=2)
      is_2l = true;
    else if((int)llep.size()==1 && (int)GoodJets.size()>=2)
      is_ljj = true;
    
      
    /********************************************************************
     *                               bJets                              *
     ********************************************************************/

    //All bJets
    if(is_ljj){
      float bJetEta = -999.0;
      float bJetEta_MedWP = -999.0;
      h.bjets[0]->Fill((int)bTagJets.size());
      h.bjets[1]->Fill((int)bTagJets_MedWP.size());
      for(int i=0; i<(int)bTagJets.size(); i++){
	h.bjets[2]->Fill(bTagJets.at(i).v.Pt());
	h.bjets[3]->Fill(bTagJets.at(i).v.Eta());
	h.bJets[0]->Fill(bTagJets.at(i).v.Pt(),fabs(bTagJets.at(i).v.Eta()));
      }
      //bJets Eta binned
      //cout<<"BTagDeepB Score for Jets that pass B hadron flavor only!"<<endl;
      for(int i=0; i<(int)bTagJets.size(); i++){
	bJetEta = fabs(bTagJets.at(i).v.Eta());
	if(0.0<bJetEta && bJetEta<0.8)
	  h.bjets[4]->Fill(bTagJets.at(i).v.Pt());
	if(0.8<bJetEta && bJetEta<1.6)
	  h.bjets[5]->Fill(bTagJets.at(i).v.Pt());
	if(1.6<bJetEta && bJetEta<2.5)
	  h.bjets[6]->Fill(bTagJets.at(i).v.Pt());
      }
      //All bJets MedWP
      for(int i=0; i<(int)bTagJets_MedWP.size(); i++){
	h.bjets[7]->Fill(bTagJets_MedWP.at(i).v.Pt());
	h.bjets[8]->Fill(bTagJets_MedWP.at(i).v.Eta());
	h.bJets[1]->Fill(bTagJets_MedWP.at(i).v.Pt(),fabs(bTagJets_MedWP.at(i).v.Eta()));
      }
      //bJets MedWP Eta binned
      //cout<<"BTagDeepB Score for Jets that pass B hadron flavor and Medium WP"<<endl;
      for(int i=0; i<(int)bTagJets_MedWP.size(); i++){
	bJetEta_MedWP = fabs(bTagJets_MedWP.at(i).v.Eta());
	if(0.0<bJetEta_MedWP && bJetEta_MedWP<0.8)
	  h.bjets[9]->Fill(bTagJets_MedWP.at(i).v.Pt());
	if(0.8<bJetEta_MedWP && bJetEta_MedWP<1.6)
	  h.bjets[10]->Fill(bTagJets_MedWP.at(i).v.Pt());
	if(1.6<bJetEta_MedWP && bJetEta_MedWP<2.5)
	  h.bjets[11]->Fill(bTagJets_MedWP.at(i).v.Pt());
      }
      
      /********************************************************************
       *                               cJets                              *
       ********************************************************************/
      
      //All cJets
      float cJetEta = -999.0;
      float cJetEta_Mis = -999.0;
      h.cjets[0]->Fill((int)cTagJets.size());
      h.cjets[1]->Fill((int)cTagJets_Mis.size());
      for(int i=0; i<(int)cTagJets.size(); i++){
	h.cjets[2]->Fill(cTagJets.at(i).v.Pt());
	h.cjets[3]->Fill(cTagJets.at(i).v.Eta());
	h.cJets[0]->Fill(cTagJets.at(i).v.Pt(),fabs(cTagJets.at(i).v.Eta()));
      }
      //cJets Eta binned
      for(int i=0; i<(int)cTagJets.size(); i++){
	cJetEta = fabs(cTagJets.at(i).v.Eta());
	if(0.0<cJetEta && cJetEta<0.8)
	  h.cjets[4]->Fill(cTagJets.at(i).v.Pt());
	if(0.8<cJetEta && cJetEta<1.6)
	  h.cjets[5]->Fill(cTagJets.at(i).v.Pt());
	if(1.6<cJetEta && cJetEta<2.5)
	  h.cjets[6]->Fill(cTagJets.at(i).v.Pt());
      }
      //cTagJets Misidentified
      for(int i=0; i<(int)cTagJets_Mis.size(); i++){
	h.cjets[7]->Fill(cTagJets_Mis.at(i).v.Pt());
	h.cjets[8]->Fill(cTagJets_Mis.at(i).v.Eta());
	h.cJets[1]->Fill(cTagJets_Mis.at(i).v.Pt(),fabs(cTagJets_Mis.at(i).v.Eta()));
      }
      //cJets MisIdentified Eta binned
      for(int i=0; i<(int)cTagJets_Mis.size(); i++){
	cJetEta_Mis = fabs(cTagJets_Mis.at(i).v.Eta());
	if(0.0<cJetEta_Mis && cJetEta_Mis<0.8)
	  h.cjets[9]->Fill(cTagJets_Mis.at(i).v.Pt());
	if(0.8<cJetEta_Mis && cJetEta_Mis<1.6)
	  h.cjets[10]->Fill(cTagJets_Mis.at(i).v.Pt());
	if(1.6<cJetEta_Mis && cJetEta_Mis<2.5)
	  h.cjets[11]->Fill(cTagJets_Mis.at(i).v.Pt());
      }
      
      /********************************************************************
       *                           LightJets                              *
       ********************************************************************/  
      
      //LightJets
      float lJetEta = -999.0;
      float lJetEta_Mis = -999.0;
      h.ljets[0]->Fill((int)LightTagJets.size());
      h.ljets[1]->Fill((int)LightTagJets_Mis.size());
      for(int i=0; i<(int)LightTagJets.size(); i++){
	h.ljets[2]->Fill(LightTagJets.at(i).v.Pt());
	h.ljets[3]->Fill(LightTagJets.at(i).v.Eta());
	h.lJets[0]->Fill(LightTagJets.at(i).v.Pt(),fabs(LightTagJets.at(i).v.Eta()));
      }
      //LightJets Eta binned
      for(int i=0; i<(int)LightTagJets.size(); i++){
	lJetEta = fabs(LightTagJets.at(i).v.Eta());
	if(0.0<lJetEta && lJetEta<0.8)
	  h.ljets[4]->Fill(LightTagJets.at(i).v.Pt());
	if(0.8<lJetEta && lJetEta<1.6)
	  h.ljets[5]->Fill(LightTagJets.at(i).v.Pt());
	if(1.6<lJetEta && lJetEta<2.5)
	  h.ljets[6]->Fill(LightTagJets.at(i).v.Pt());
      }
      //Light Jets Misidentified
      for(int i=0; i<(int)LightTagJets_Mis.size(); i++){
	h.ljets[7]->Fill(LightTagJets_Mis.at(i).v.Pt());
	h.ljets[8]->Fill(LightTagJets_Mis.at(i).v.Eta());
	h.lJets[1]->Fill(LightTagJets_Mis.at(i).v.Pt(),fabs(LightTagJets_Mis.at(i).v.Eta()));
      }
      //LightJets MisIdentified Eta binned
      for(int i=0; i<(int)LightTagJets_Mis.size(); i++){
	lJetEta_Mis = fabs(LightTagJets_Mis.at(i).v.Eta());
	if(0.0<lJetEta_Mis && lJetEta_Mis<0.8)
	  h.ljets[9]->Fill(LightTagJets_Mis.at(i).v.Pt());
	if(0.8<lJetEta_Mis && lJetEta_Mis<1.6)
	  h.ljets[10]->Fill(LightTagJets_Mis.at(i).v.Pt());
	if(1.6<lJetEta_Mis && lJetEta_Mis<2.5)
	  h.ljets[11]->Fill(LightTagJets_Mis.at(i).v.Pt());
      } 
    }
     
  }
  return kTRUE;
}

void VLLAna::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
  
  _HstFile->Write();
  _HstFile->Close();

  //Output to screen
  cout<<"Total events ran = "<<nEvtRan<<endl;
  cout<<"Total events  = "<<nEvtTotal<<endl;
}

void VLLAna::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void VLLAna::BookHistograms()
{
  //Event Hists
  h.nevt[0]       = new TH1F("nEvents","Total events",4,0,4);
  h.nevt[1]       = new TH1F("nEvents_2L","nEvents_2L",4,0,4);
  h.nevt[2]       = new TH1F("nEvents_1L1T","nEvents_1L1T",4,0,4);
  h.nevt[3]       = new TH1F("nEvents_1L2J","nEvents_1L2J",4,0,4);
  
  //MET Filter
  h.metfilter[0]  = new TH1F("METfilter_goodVertices","METfilter_goodVertices",5,-1,4);
  h.metfilter[1]  = new TH1F("METfilter_globalSuperTightHalo2016Filter","METfilter_globalSuperTightHalo2016Filter",5,-1,4);
  h.metfilter[2]  = new TH1F("METfilter_HBHENoiseFilter","METfilter_HBHENoiseFilter",5,-1,4);
  h.metfilter[3]  = new TH1F("METfilter_HBHENoiseIsoFilter","METfilter_HBHENoiseIsoFilter",5,-1,4);
  h.metfilter[4]  = new TH1F("METfilter_EcalDeadCellTriggerPrimitiveFilter","METfilter_EcalDeadCellTriggerPrimitiveFilter",5,-1,4);
  h.metfilter[5]  = new TH1F("METfilter_BadPFMuonFilter","METfilter_BadPFMuonFilter",5,-1,4);
  h.metfilter[6]  = new TH1F("METfilter_eeBadScFilter","METfilter_eeBadScFilter",5,-1,4);
  h.metfilter[7]  = new TH1F("METfilter_GoodEvt2016","METfilter_GoodEvt2016",5,-1,4);
  h.metfilter[8]  = new TH1F("METfilter_GoodEvt2017","METfilter_GoodEvt2017",5,-1,4);
  h.metfilter[9]  = new TH1F("METfilter_GoodEvt2018","METfilter_GoodEvt2018",5,-1,4);
  h.metfilter[10] = new TH1F("METfilter_GoodEvt","METfilter_GoodEvt",5,-1,4);
  
  //Light leptons
  h.llep[0]      = new TH1F("n_LightLeptons","n_LightLeptons",10,0,10);     

  //Genllep
  h.genllep[0]   = new TH1F("n_GenLightLeptons","n_GenLightLeptons",10,0,10);

  //Mother Plot
  h.mom[0]       = new TH1F("GenEle_Mother","GenEle_Mother",1200,-600,600);
  h.mom[1]       = new TH1F("GenMu_Mother","GenMu_Mother",1200,-600,600);
  h.mom[2]       = new TH1F("GenTau_Mother","GenTau_Mother",1200,-600,600);

  //dR Plots
  h.dR[0]        = new TH1F("dR_Ele_GenEle","dR_Ele_GenEle",100,0,1);
  h.dR[1]        = new TH1F("dR_Mu_GenMu","dR_Mu_GenMu",100,0,1);
  h.dR[2]        = new TH1F("dR_Taus_Gentaus","dR_Taus_GenTaus",100,0,1);
  h.dR[3]        = new TH1F("dR_LeadLep_SubLeadLep","dR_LeadLep_SubLeadLep",100,0,1);
  h.dR[4]        = new TH1F("dR_LeadLep_LeadTau","dR_LeadLep_LeadTau",100,0,1);
  h.dR[5]        = new TH1F("dR_LeadLep_LeadJet","dR_LeadLep_LeadJet",100,0,1);
  h.dR[6]        = new TH1F("dR_LeadLep_SubLeadJet","dR_LeadLep_SubLeadJet",100,0,1);
  
  //GenElectrons
  h.genele[0]    = new TH1F("nGenEle","nGenEle", 10, 0, 10);
  h.genele[1]    = new TH1F("GenEle_pT","GenEle_pT",200,0,200);
  h.genele[2]    = new TH1F("GenEle_Eta","GenEle_Eta",80,-4,4);
  h.genele[3]    = new TH1F("GenEle_Phi","GenEle_Phi",80,-4,4);
  
  //GenMuons
  h.genmu[0]     = new TH1F("nGenMu","nGenMu", 10, 0, 10);
  h.genmu[1]     = new TH1F("GenMu_pT","GenMu_pT",200,0,200);
  h.genmu[2]     = new TH1F("GenMu_Eta","GenMu_Eta",80,-4,4);
  h.genmu[3]     = new TH1F("GenMu_Phi","GenMu_Phi",80,-4,4);
  
  //GenTaus
  h.gentau[0]    = new TH1F("nGenTau","nGenTau", 10, 0, 10);
  h.gentau[1]    = new TH1F("GenTau_pT","GenTau_pT",200,0,200);
  h.gentau[2]    = new TH1F("GenTau_Eta","GenTau_Eta",80,-4,4);
  h.gentau[3]    = new TH1F("GenTau_Phi","GenTau_Phi",80,-4,4);
  
  //Electrons
  h.electrons[0] = new TH1F("nEle","nEle", 10, 0, 10);
  h.electrons[1] = new TH1F("Ele_pT","Ele_pT",200,0,200);
  h.electrons[2] = new TH1F("Ele_Eta","Ele_Eta",80,-4,4);
  h.electrons[3] = new TH1F("Ele_Phi","Ele_Phi",80,-4,4);
  
  //Muons
  h.muons[0]     = new TH1F("nMuons","nMuons", 10, 0, 10);
  h.muons[1]     = new TH1F("Muon_pT","Muon_pT",200,0,200);
  h.muons[2]     = new TH1F("Muon_Eta","Muon_Eta",80,-4,4);
  h.muons[3]     = new TH1F("Muon_Phi","Muon_Phi",80,-4,4);
  
  //Taus
  h.taus[0]      = new TH1F("nTaus","nTaus", 10, 0, 10);
  h.taus[1]      = new TH1F("Tau_pT","Tau_pT",200,0,200);
  h.taus[2]      = new TH1F("Tau_Eta","Tau_Eta",80,-4,4);
  h.taus[3]      = new TH1F("Tau_Phi","Tau_Phi",80,-4,4);

  //CutFlow(Debugging)
  h.mucut = new TH1F("mucut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=Iso:0.15",10,0,10);
  h.mucut->Sumw2();
  h.elecut = new TH1F("elcut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=muoncleaning",10,0,10);
  h.elecut->Sumw2();
  h.taucut = new TH1F("taucut","0=All,1=NewDM,2=AntiJet,3=AntiEle,4=AntiMu,5=Prompt,6=LepClean,7=Eta,8=PT",10,0,10);
  h.taucut->Sumw2();

  //Jets
  h.jets[0]      = new TH1F("nJet","nJet", 10, 0, 10);
  h.jets[1]      = new TH1F("Jet_pT","Jet_pT",200,0,200);
  h.jets[2]      = new TH1F("Jet_Eta","Jet_Eta",80,-4,4);
  h.jets[3]      = new TH1F("Jet_Phi","Jet_Phi",80,-4,4);
  
  //bJets: 1D histograms
  h.bjets[0]      = new TH1F("nbJet","nbJet", 10, 0, 10);
  h.bjets[1]      = new TH1F("nbJet_MedWP","nbJet_MedWP", 10, 0, 10);
  h.bjets[2]      = new TH1F("bJet_pT","bJet_pT",100,0,1000);
  h.bjets[3]      = new TH1F("bJet_Eta","bJet_Eta",60,-3,3);
  h.bjets[4]      = new TH1F("bJet_pT_Eta<0.8","bJet_pT_Eta<0.8",100,0,1000);
  h.bjets[5]      = new TH1F("bJet_pT_0.8<Eta<1.6","bJet_pT_0.8<Eta<1.6",100,0,1000);
  h.bjets[6]      = new TH1F("bJet_pT_1.6<Eta<2.5","bJet_pT_1.6<Eta<2.5",100,0,1000);
  h.bjets[7]      = new TH1F("bJet_MedWP_pT","bJet_MedWP_pT",100,0,1000);
  h.bjets[8]      = new TH1F("bJet_MedWP_Eta","bJet_MedWP_Eta",60,-3,3);
  h.bjets[9]      = new TH1F("bJet_MedWP_pT_Eta<0.8","bJet_MedWP_pT_Eta<0.8",100,0,1000);
  h.bjets[10]     = new TH1F("bJet_MedWP_pT_0.8<Eta<1.6","bJet_MedWP_pT_0.8<Eta<1.6",100,0,1000);
  h.bjets[11]     = new TH1F("bJet_MedWP_pT_1.6<Eta<2.5","bJet_MedWP_pT_1.6<Eta<2.5",100,0,1000);
  
  //bJets:2D histograms
  float x_bin_pT[10] = {20,30,50,70,100,140,200,300,600,1000};
  float y_bin_eta[4] = {0.0,0.8,1.6,3.0};
  //h.bJets[0]     = new TH2F("bJet_PtEta","bJet_PtEta",100,0,1000,9,0,3);
  //h.bJets[1]     = new TH2F("bJet_MedWP_PtEta","bJet_MedWP_PtEta",100,0,1000,9,0,3);
  h.bJets[0]     = new TH2F("bJet_PtEta","bJet_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);
  h.bJets[1]     = new TH2F("bJet_MedWP_PtEta","bJet_MedWP_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);

  //cJets: 1D histograms
  h.cjets[0]      = new TH1F("ncJet","ncJet", 10, 0, 10);
  h.cjets[1]      = new TH1F("ncJet_Mis","ncJet_Mis", 10, 0, 10);//Mis:Mistagged
  h.cjets[2]      = new TH1F("cJet_pT","cJet_pT",200,0,200);
  h.cjets[3]      = new TH1F("cJet_Eta","cJet_Eta",60,-3,3);
  h.cjets[4]      = new TH1F("cJet_pT_Eta<0.8","cJet_pT_Eta<0.8",200,0,200);
  h.cjets[5]      = new TH1F("cJet_pT_0.8<Eta<1.6","cJet_pT_0.8<Eta<1.6",200,0,200);
  h.cjets[6]      = new TH1F("cJet_pT_1.6<Eta<2.5","cJet_pT_1.6<Eta<2.5",200,0,200);
  h.cjets[7]      = new TH1F("cJet_Mis_pT","cJet_Mis_pT",200,0,200);
  h.cjets[8]      = new TH1F("cJet_Mis_Eta","cJet_Mis_Eta",60,-3,3);
  h.cjets[9]      = new TH1F("cJet_Mis_pT_Eta<0.8","cJet_Mis_pT_Eta<0.8",200,0,200);
  h.cjets[10]     = new TH1F("cJet_Mis_pT_0.8<Eta<1.6","cJet_Mis_pT_0.8<Eta<1.6",200,0,200);
  h.cjets[11]     = new TH1F("cJet_Mis_pT_1.6<Eta<2.5","cJet_Mis_pT_1.6<Eta<2.5",200,0,200);

  //bJets:2D histograms

  //h.cJets[0]     = new TH2F("cJet_PtEta","cJet_PtEta",200,0,200,9,0,3);
  //h.cJets[1]     = new TH2F("cJet_Mis_PtEta","cJet_Mis_PtEta",200,0,200,9,0,3);
  h.cJets[0]     = new TH2F("cJet_PtEta","cJet_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);
  h.cJets[1]     = new TH2F("cJet_Mis_PtEta","cJet_Mis_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);

  //lJets: 1D histograms
  h.ljets[0]      = new TH1F("nLightJet","nbJet", 10, 0, 10);
  h.ljets[1]      = new TH1F("nLightJet_Mis","nLightJet_Mis", 10, 0, 10);
  h.ljets[2]      = new TH1F("LightJet_pT","LightJet_pT",200,0,200);
  h.ljets[3]      = new TH1F("LightJet_Eta","LightJet_Eta",60,-3,3);
  h.ljets[4]      = new TH1F("LightJet_pT_Eta<0.8","LightJet_pT_Eta<0.8",200,0,200);
  h.ljets[5]      = new TH1F("LightJet_pT_0.8<Eta<1.6","LightJet_pT_0.8<Eta<1.6",200,0,200);
  h.ljets[6]      = new TH1F("LightJet_pT_1.6<Eta<2.5","LightJet_pT_1.6<Eta<2.5",200,0,200);
  h.ljets[7]      = new TH1F("LightJet_Mis_pT","LightJet_Mis_pT",200,0,200);
  h.ljets[8]      = new TH1F("LightJet_Mis_Eta","LightJet_Mis_Eta",60,-3,3);
  h.ljets[9]      = new TH1F("LightJet_Mis_pT_Eta<0.8","LightJet_Mis_pT_Eta<0.8",200,0,200);
  h.ljets[10]     = new TH1F("LightJet_Mis_pT_0.8<Eta<1.6","LightJet_Mis_pT_0.8<Eta<1.6",200,0,200);
  h.ljets[11]     = new TH1F("LightJet_Mis_pT_1.6<Eta<2.5","LightJet_Mis_pT_1.6<Eta<2.5",200,0,200);
  
  //lJets:2D histograms
  //h.lJets[0]     = new TH2F("LightJet_PtEta","LightJet_PtEta",200,0,200,9,0,3);
  //h.lJets[1]     = new TH2F("LightJet_Mis_PtEta","LightJet_Mis_PtEta",200,0,200,9,0,3);
  h.lJets[0]      = new TH2F("LightJet_PtEta","LightJet_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);
  h.lJets[1]      = new TH2F("LightJet_Mis_PtEta","LightJet_Mis_PtEta",(sizeof(x_bin_pT)/ sizeof(x_bin_pT[0])-1),x_bin_pT,(sizeof(y_bin_eta)/sizeof(y_bin_eta[0])-1),y_bin_eta);


  //bTagWeight
  h.bTagWeight[0] = new TH1F("bTagWeights","bTagWeights",130,0.7,2.0);
  
}
void VLLAna::SortPt(int opt){

  if(opt==0){
    for(int i=0; i<(int)tempGoodMu.size()-1; i++){
      for(int j=i+1; j<(int)tempGoodMu.size(); j++){
	if( tempGoodMu[i].v.Pt() < tempGoodMu[j].v.Pt() ) swap(tempGoodMu.at(i),tempGoodMu.at(j));
      }
    }
  }
  
  if(opt==1){
    for(int i=0; i<(int)GoodMu.size()-1; i++){
      for(int j=i+1; j<(int)GoodMu.size(); j++){
	if(GoodMu[i].v.Pt() < GoodMu[j].v.Pt() ) swap(GoodMu.at(i),GoodMu.at(j));
      }
    }
  }

  if(opt==2){
    for(int i=0; i<(int)tempGoodEle.size()-1; i++){
      for(int j=i+1; j<(int)tempGoodEle.size(); j++){
	if(tempGoodEle[i].v.Pt() < tempGoodEle[j].v.Pt() ) swap(tempGoodEle.at(i),tempGoodEle.at(j));
      }
    }
  }
  
  if(opt==3){
    for(int i=0; i<(int)GoodEle.size()-1; i++){
      for(int j=i+1; j<(int)GoodEle.size(); j++){
	if(GoodEle[i].v.Pt() < GoodEle[j].v.Pt() ) swap(GoodEle.at(i),GoodEle.at(j));
      }
    }
  }

  if(opt==4){
    for(int i=0; i<(int)llep.size()-1; i++){
      for(int j=i+1; j<(int)llep.size(); j++){
	if( llep[i].v.Pt() < llep[j].v.Pt() ) swap(llep.at(i),llep.at(j));
      }
    }
  }
  if(opt==5){
    for(int i=0; i<(int)GoodTaus.size()-1; i++){
      for(int j=i+1; j<(int)GoodTaus.size(); j++){
	if( GoodTaus[i].v.Pt() < GoodTaus[j].v.Pt() ) swap(GoodTaus.at(i),GoodTaus.at(j));
      }
    }
  }
  if(opt==6){
    for(int i=0; i<(int)GoodJets.size()-1; i++){
      for(int j=i+1; j<(int)GoodJets.size(); j++){
	if( GoodJets[i].v.Pt() < GoodJets[j].v.Pt() ) swap(GoodJets.at(i),GoodJets.at(j));
      }
    }
  }

  
}

float VLLAna::delta_phi(float phi1, float phi2)
{
  //Calculate the correct deltaPhi=phi1-phi2
  phi1 = TVector2::Phi_0_2pi(phi1);
  phi2 = TVector2::Phi_0_2pi(phi2);
  float dphi = fabs(phi1 - phi2);
  if(dphi>TMath::Pi()) dphi = 2*TMath::Pi() - dphi;
  return dphi;
}

float VLLAna::delta_Eta(float eta1, float eta2)
{
  //Calculate the correct deltaPhi=phi1-phi2
  float deta = fabs(fabs(eta1) - fabs(eta2));
  return deta;
}

int VLLAna::GenMother(int ind, int mom_ind)
{
  int p_id = GenPart_pdgId[ind];
  int m_id = GenPart_pdgId[mom_ind];
  while(p_id==m_id){
	ind = mom_ind;
	mom_ind = GenPart_genPartIdxMother[ind];
	p_id = GenPart_pdgId[ind];
	m_id = GenPart_pdgId[mom_ind];
  }
  return m_id;
}
