#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TVirtualFitter.h"
#include "TGraph.h"
using std::cout;
using std::endl;

void SetHistoStyle(TH2F *histo, TString title ,TString xlabel, TString ylabel){
  histo->SetLineColor(kBlack);
  histo->SetLineWidth(2);
  histo->SetMarkerStyle(20);
  histo->SetMarkerSize(1.2);
  histo->SetTitle(title);
    
  //Y-axis
  histo->GetYaxis()->SetTitle(ylabel);
  histo->GetYaxis()->SetTitleFont(43);
  histo->GetYaxis()->SetTitleSize(20);
  histo->GetYaxis()->SetTitleOffset(1.6);
  histo->GetYaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetLabelSize(20);
  histo->GetYaxis()->CenterTitle();
  
  //X-axis
  histo->GetXaxis()->SetTitle(xlabel);
  histo->GetXaxis()->SetTitleFont(43);
  histo->GetXaxis()->SetTitleSize(20);
  histo->GetXaxis()->SetTitleOffset(1.5);
  histo->GetXaxis()->SetLabelFont(43);
  histo->GetXaxis()->SetLabelSize(20); 
  histo->GetXaxis()->CenterTitle();

  //Z-axis
  histo->GetZaxis()->SetRangeUser(0.0, 1.0);
}

void eff_maps()
{
  //TFile *ftt = new TFile("hst_TTBar.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_TTBar_TTToSemiLeptonic_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_TTBar_TTTo2L2Nu_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_DYJetsToLL_M10to50_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_DYJetsToLL_M50_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_HTbinnedWJets_Inclusive_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_ZZ_ZZTo4L_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_ZZ_ZZTo2Q2Nu_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_ZZ_ZZTo2Q2L_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_ZZ_ZZTo2L2Nu_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WZ_WZTo3LNu_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WZ_WZTo2Q2L_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WZ_WZTo1L1Nu2Q_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WW_WWTo1L1Nu2Q_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WW_WWTo2L2Nu_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_WW_WWTo4Q_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_SingleTop_s-channel_LeptonDecays_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_SingleTop_t-channel_AntiTop_InclusiveDecays_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_SingleTop_t-channel_Top_InclusiveDecays_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_SingleTop_tW_AntiTop_InclusiceDecays_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_SingleTop_tW_Top_InclusiveDecays_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_20to30_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_30to50_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_50to80_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_80to120_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_120to170_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_170to300_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_300to470_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_470to600_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_600to800_sample.root");
  //TFile *ftt = new TFile("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/hstfiles/VLL2018_1L2JAnalysis_bTagEff_Dec13_v1_QCD_MuEnriched_800to1000_sample.root");
  
	  
  TString plots[6] = {"bJet_PtEta",
		      "bJet_MedWP_PtEta",
		      "cJet_PtEta",
		      "cJet_Mis_PtEta",
		      "LightJet_PtEta",
		      "LightJet_Mis_PtEta"
  };
  
  TString plotname1;
  TH2F *h[50], *hb,*hc, *hl, *ratio;

  for(int i=0; i<6; i++){
    plotname1 = plots[i];
    
    //Now open the respective histograms from the file
    h[i] = (TH2F*)ftt ->Get(plotname1);
  }

  //Define a new canvas
  TCanvas *c1 = new TCanvas("c1","c1",1600,1200) ;
  gStyle->SetOptStat(0);
  c1->SetLogx(1);
  hb = (TH2F*)h[1]->Clone();
  //hb->SetTitle("bJetEfficiency");
  hb->Divide(h[0]);
  hb->Draw("COLZ");
  hb->Draw("TEXT SAME");
  SetHistoStyle(hb,"bJetEfficiency","Jet_pT", "Jet_Eta");
  c1->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/QCDMuEnriched/bJetEff_20To30.jpg");

  TCanvas *c2 = new TCanvas("c2","c2",1600,1200) ;
  gStyle->SetOptStat(0);
  c2->SetLogx(1);
  hc = (TH2F*)h[3]->Clone();
  hc->GetXaxis()->SetTitle("Jet Pt");
  hc->GetYaxis()->SetTitle("Jet Eta");
  //hc->SetTitle("cJetMisTaggingEfficiency");
  hc->Divide(h[2]);
  hc->Draw("COLZ");
  hc->Draw("TEXT SAME");
  SetHistoStyle(hc,"cJetMisTaggingEfficiency","Jet_pT", "Jet_Eta");
  c2->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/QCDMuEnriched/cJetMisEff_20To30.jpg");
  
  TCanvas *c3 = new TCanvas("c3","c3",1600,1200) ;
  gStyle->SetOptStat(0);
  c3->SetLogx(1);
  hl = (TH2F*)h[5]->Clone();
  hl->GetXaxis()->SetTitle("Jet Pt");
  hl->GetYaxis()->SetTitle("Jet Eta");
  //hl->SetTitle("LightJetMisTaggingEfficiency");
  hl->Divide(h[4]);
  hl->Draw("COLZ");
  hl->Draw("TEXT SAME");
  SetHistoStyle(hl,"LightJetMisTaggingEfficiency","Jet_pT", "Jet_Eta");
  c3->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/QCDMuEnriched/LightJetMisEff_20To30.jpg");
    
}
