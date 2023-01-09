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


void eff_maps_uncertainity()
{
  //TFile *ftt = new TFile("hst_TTBar.root");
  TFile *ftt = new TFile("VLL2018_1L2JAnalysis_bTagSF_Nov23_v3_TTBar_TTToSemiLeptonic_sample.root");

  TString plots[6] = {"bJet_PtEta",
		      "bJet_MedWP_PtEta",
		      "cJet_PtEta",
		      "cJet_Mis_PtEta",
		      "LightJet_PtEta",
		      "LightJet_Mis_PtEta"
  };
  
  TString plotname1;
  TH2F *h[50], *hb,*hc, *hl,*hb_err, *hc_err, *hl_err;
  vector<float> binwiseError_h[6], binwiseIntegral_h[6], multiplicativeErrorpropagator[3];
  
  for(int i=0; i<6; i++){
    binwiseError_h[i].clear();
    binwiseIntegral_h[i].clear();
    plotname1 = plots[i];
    //Now open the respective histograms from the file
    h[i] = (TH2F*)ftt ->Get(plotname1);
    //Calculating bin wise error for the numerator and denominator histograms
    for(int j =1; j<10; j++){
      for(int k =1; k<4; k++){
	binwiseIntegral_h[i].push_back(h[i]->GetBinContent(j,k));
	binwiseError_h[i].push_back(h[i]->GetBinError(j,k));
      }
    }
  }
  
  cout<<"binwiseIntegral"<<endl;  
  for(int i=0; i<binwiseIntegral_h[0].size(); i++){
    cout<<binwiseIntegral_h[0][i]<<endl;
  }
  cout<<"=================================================================="<<endl;

  cout<<"binwiseError"<<endl;  
  for(int i=0; i<binwiseError_h[0].size(); i++){
    cout<<binwiseError_h[0][i]<<endl;
  }
  cout<<"=================================================================="<<endl;
  
  for(int k = 0; k<(float)binwiseError_h[0].size(); k++){
    multiplicativeErrorpropagator[0].push_back(sqrt((pow(binwiseError_h[0][k],2)/pow(binwiseIntegral_h[0][k],2))+(pow(binwiseError_h[1][k],2)/pow(binwiseIntegral_h[1][k],2))));//b
    multiplicativeErrorpropagator[1].push_back(sqrt((pow(binwiseError_h[2][k],2)/pow(binwiseIntegral_h[2][k],2))+(pow(binwiseError_h[3][k],2)/pow(binwiseIntegral_h[3][k],2))));//c
    multiplicativeErrorpropagator[2].push_back(sqrt((pow(binwiseError_h[4][k],2)/pow(binwiseIntegral_h[4][k],2))+(pow(binwiseError_h[5][k],2)/pow(binwiseIntegral_h[5][k],2))));//light jet
  }
  
  for(int i=0; i<multiplicativeErrorpropagator[0].size();i++){
    cout<<multiplicativeErrorpropagator[0][i]<<endl;
  }


  //Define a new canvas
  TCanvas *c1 = new TCanvas("c1","c1",1600,1200) ;
  gStyle->SetOptStat(0);
  c1->SetLogx(1);
  hb = (TH2F*)h[1]->Clone();
  hb->Divide(h[0]);

  for(int i = 0; i<9; i++){
    for(int j = 0; j<3; j++){
      Int_t bin = hb->GetBin(i+1,j+1);
      cout<<bin<<endl;
      cout<<hb->GetBinContent(bin)<<endl;
    }
  }

  
  int a = 13;
  int b = 3;
  while(a<21 && b<25){
    hb->SetBinContent(a,(hb->GetBinContent(a))*(multiplicativeErrorpropagator[0][b]));
    a++;
    b+=3;
  }
  int c = 24;
  int d = 4;
  while(c<32 && d<26){
    hb->SetBinContent(c,(hb->GetBinContent(c))*(multiplicativeErrorpropagator[0][d]));
    c++;
    d+=3;
  }
  
  int e = 35;
  int f = 5;
  while(e<43 && f<27){
    hb->SetBinContent(e,(hb->GetBinContent(e))*(multiplicativeErrorpropagator[0][f]));
    e++;
    f+=3;
  }
  
  hb->Draw("COLZ");
  hb->Draw("TEXT SAME");
  SetHistoStyle(hb,"bJetEfficiency_StatError","Jet_pT", "Jet_Eta");
  c1->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_FullSample/bJetEfficiency_StatError.png");
  //c1->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_LocalFile/bJetEfficiency_StatError.png");
  
  TCanvas *c2 = new TCanvas("c2","c2",1600,1200) ;
  gStyle->SetOptStat(0);
  c2->SetLogx(1);
  hc = (TH2F*)h[3]->Clone();
  hc->GetXaxis()->SetTitle("Jet Pt");
  hc->GetYaxis()->SetTitle("Jet Eta");
  hc->Divide(h[2]);

  while(a<21 && b<25){
    hc->SetBinContent(a,(hc->GetBinContent(a))*(multiplicativeErrorpropagator[1][b]));
    a++;
    b+=3;
  }
  while(c<32 && d<26){
    hc->SetBinContent(c,(hc->GetBinContent(c))*(multiplicativeErrorpropagator[1][d]));
    c++;
    d+=3;
  }
  
  while(e<43 && f<27){
    hc->SetBinContent(e,(hc->GetBinContent(e))*(multiplicativeErrorpropagator[1][f]));
    e++;
    f+=3;
  }
  hc->Draw("COLZ");
  hc->Draw("TEXT SAME");
  SetHistoStyle(hc,"cJetMisTaggingEfficiency_StatError","Jet_pT", "Jet_Eta");
  c2->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_FullSample/cJetMisTaggingEfficiency_StatError.png");
  //c2->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_LocalFile/cJetMisTaggingEfficiency_StatError.png");
    
  TCanvas *c3 = new TCanvas("c3","c3",1600,1200) ;
  gStyle->SetOptStat(0);
  c3->SetLogx(1);
  hl = (TH2F*)h[5]->Clone();
  hl->GetXaxis()->SetTitle("Jet Pt");
  hl->GetYaxis()->SetTitle("Jet Eta");
  hl->Divide(h[4]);

  while(a<21 && b<25){
    hl->SetBinContent(a,(hl->GetBinContent(a))*(multiplicativeErrorpropagator[2][b]));
    a++;
    b+=3;
  }
  while(c<32 && d<26){
    hl->SetBinContent(c,(hl->GetBinContent(c))*(multiplicativeErrorpropagator[2][d]));
    c++;
    d+=3;
  }
  
  while(e<43 && f<27){
    hl->SetBinContent(e,(hl->GetBinContent(e))*(multiplicativeErrorpropagator[2][f]));
    e++;
    f+=3;
  }
  hl->Draw("COLZ");
  hl->Draw("TEXT SAME");
  SetHistoStyle(hl,"LightJetMisTaggingEfficiency_StatError","Jet_pT", "Jet_Eta");
  c3->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_FullSample/LightJetMisTaggingEfficiency_StatError.png");
  //c3->SaveAs("/home/ykumar/Yash/Work/VLLAnalysis_2022/bTagEfficiency/Efficiency_Maps/TTBar_SemiLeptonic_LocalFile/LightJetMisTaggingEfficiency_StatError.png");
  
}
