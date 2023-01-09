#include "TF1.h"
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

void decorate(TGraph *h, TString gtitle, float gmax, float gmin, 
	      int markercolor, int markerstyle, int linecolor, int linewidth);
void decorateHist(TH1*h,const char* xtitle, const char* ytitle, const char* title,
	      int linecolor, int linewidth, int markercolor, int markerstyle, int tofill);
void decorate(TLegend *g, float textSize, TString legendheader);
float get_nevents(TH1F *hst, float bin_lo, float bin_hi);
float get_nevents_err(TH1F *hst, float bin_lo, float bin_hi);
void SetOverflowBin(TH1F *histo);

void make_efff()
{
  ofstream outfile;
  outfile.open("bTagEfficiency.txt");
    
  TFile *ftt = new TFile("hst_TTBar.root");
  
  // Determine the bin-edges; efficiency will be calculated in these bins
  float lowed[] =  {20,30,50,70,100,140,200,300,600};
  float hied[]  =  {30,50,70,100,140,200,300,600,1000};
  
  int nbin = 9; 
  
  //Open the histogram
  TString etarange[3]  = {"_Eta<0.8", "_0.8<Eta<1.6", "_1.6<Eta<2.5"};
  vector<TString> bJetDen, bJetNum, cJetDen, cJetNum, LightJetDen, LightJetNum;
  TH1F *bHistDen[5];
  TH1F *bHistNum[5];
  TH1F *cHistDen[5];
  TH1F *cHistNum[5];
  TH1F *lHistDen[5];
  TH1F *lHistNum[5];

  //Clearing the vectors
  bJetDen.clear();
  cJetDen.clear();
  LightJetDen.clear();
  bJetNum.clear();
  cJetNum.clear();
  LightJetNum.clear();
  
  for(int j=0; j<3; j++){
    bJetDen.push_back("bJet_pT"+etarange[j]);
    bJetNum.push_back("bJet_MedWP_pT"+etarange[j]);
    cJetDen.push_back("cJet_pT"+etarange[j]);
    cJetNum.push_back("cJet_Mis_pT"+etarange[j]);
    LightJetDen.push_back("LightJet_pT"+etarange[j]);
    LightJetNum.push_back("LightJet_Mis_pT"+etarange[j]);
  }
  
  for(int i=0; i<3; i++){
    bHistDen[i] = (TH1F*)ftt->Get(bJetDen[i]);
    bHistNum[i] = (TH1F*)ftt->Get(bJetNum[i]);
    cHistDen[i] = (TH1F*)ftt->Get(cJetDen[i]);
    cHistNum[i] = (TH1F*)ftt->Get(cJetNum[i]);
    lHistDen[i] = (TH1F*)ftt->Get(LightJetDen[i]);
    lHistNum[i] = (TH1F*)ftt->Get(LightJetNum[i]);
    SetOverflowBin(bHistDen[i]);
    SetOverflowBin(bHistNum[i]);
    SetOverflowBin(cHistDen[i]);
    SetOverflowBin(cHistNum[i]);
    SetOverflowBin(lHistDen[i]);
    SetOverflowBin(lHistNum[i]);
  }

  //Declare some arrays to store the efficiency
  int n = 0;
  float x_b[150],y_b[150],x_c[150],y_c[150],x_l[150],y_l[150];
  double et_lo,et_hi;
  float et_step=0;
  for(int i=0; i<150; i++){
    x_b[i]=y_b[i]=x_c[i]=y_c[i]=x_l[i]=y_l[i]=0; 
  }

  outfile<<"EtaRange\t"<<"Ptlow\t"<<"PtHigh\t"<<"x_b\t"<<"y_b\t"<<"y_c\t"<<"y_l\t"<<endl;

  for(int j=0; j<3; j++){
    for(int i=0; i<nbin; i++){
    et_lo = lowed[i];
    et_hi = hied[i];
    et_step = et_hi - et_lo;

    float bJetdenValue = get_nevents(bHistDen[j],et_lo,et_hi);
    float bJetnumValue = get_nevents(bHistNum[j],et_lo,et_hi);
    float cJetdenValue = get_nevents(cHistDen[j],et_lo,et_hi);
    float cJetnumValue = get_nevents(cHistNum[j],et_lo,et_hi);
    float lJetdenValue = get_nevents(lHistDen[j],et_lo,et_hi);
    float lJetnumValue = get_nevents(lHistNum[j],et_lo,et_hi);

    x_b[n] = x_c[n] = x_l[n] = (et_lo+et_hi)/2;

    if(bJetnumValue>0 && bJetdenValue>0)
      y_b[n]=bJetnumValue/bJetdenValue;
    if(cJetnumValue>0 && cJetdenValue>0)
      y_c[n]=cJetnumValue/cJetdenValue;
    if(lJetnumValue>0 && lJetdenValue>0)
      y_l[n]=lJetnumValue/lJetdenValue;
    else
      y_b[n] = y_c[n] = y_l[n] = 0.0;
    
    outfile<<etarange[j]<<"\t"<<lowed[i]<<"\t"<<hied[i]<<"\t"<<x_b[n]<<"\t"<<y_b[n]<<"\t"<<y_c[n]<<"\t"<<y_l[n]<<"\t"<<endl;
    
    n++;
    }
    
    TString ca1 = "Canvas_bJet_";
    TString ca2 = "Canvas_cJet_";
    TString ca3 = "Canvas_LightJet_";
    TString pT1 = "Efficiency Vs bJet_pT";
    TString pT2 = "Efficiency Vs cJet_pT";
    TString pT3 = "Efficiency Vs LightJet_pT";
    
    
    // Open a canvas
    TCanvas *c1 = new TCanvas(ca1 + to_string(j),ca1 + to_string(j),800,600);
    //Declare the graph
    TGraphErrors *g1 = new TGraphErrors(nbin,x_b,y_b);
    //decorate the graph
    decorate(g1,";Jet p_{T} [GeV]; Efficiency",0.5,1.1,kRed,21,kRed,2);
    g1->SetTitle(pT1+etarange[j]);
    auto legend = new TLegend(0.85,0.60,0.55,0.70);
    legend->AddEntry(g1,"MC_TTbar","lep");
    legend->SetLineColor(17);
    legend->SetFillStyle(2);
    g1->Draw("ap");
    legend->Draw();
    g1->GetYaxis()->SetRangeUser(0,1.0);
      
    TCanvas *c2 = new TCanvas(ca2+to_string(j) ,ca2+to_string(j),800,600);
    TGraphErrors *g2 = new TGraphErrors(nbin,x_c,y_c);
    //decorate the graph
    decorate(g2,";Jet p_{T} [GeV]; Efficiency",0.5,1.1,kRed,21,kRed,2);
    g2->SetTitle(pT2+etarange[j]);
    legend->SetLineColor(17);
    legend->SetFillStyle(2);
    g2->Draw("ap");
    legend->Draw();
    g2->GetYaxis()->SetRangeUser(0,0.3);
    
    TCanvas *c3 = new TCanvas(ca3+to_string(j),ca3+to_string(j),800,600);
    TGraphErrors *g3 = new TGraphErrors(nbin,x_l,y_l);
    //decorate the graph
    decorate(g3,";Jet p_{T} [GeV]; Efficiency",1.1,0.5,kRed,21,kRed,2);
    g3->SetTitle(pT3+etarange[j]);
    legend->SetLineColor(17);
    legend->SetFillStyle(2);
    g3->Draw("ap");
    legend->Draw();
    g3->GetYaxis()->SetRangeUser(0,0.05);
  }
  outfile.close();
}

float get_nevents(TH1F *hst, float bin_lo, float bin_hi)
{
    int bin_width = hst->GetBinWidth(1);
    int ibin_begin = 1;
    float nevents = 0.;
    while ( hst->GetBinCenter(ibin_begin) < bin_lo )
        ibin_begin++;
    int ibin_end = ibin_begin;
    while ( hst->GetBinCenter(ibin_end) < bin_hi )
        ibin_end++;
    for ( int i=ibin_begin; i<ibin_end; i++ )
        nevents += hst->GetBinContent(i);

    return nevents;
}
float get_nevents_err(TH1F *hst, float bin_lo, float bin_hi)
{
    int bin_width = hst->GetBinWidth(1);
    int ibin_begin = 1;
    Double_t nevents = 0.;
    while ( hst->GetBinCenter(ibin_begin) < bin_lo )
      ibin_begin++;
    int ibin_end = ibin_begin;
    while ( hst->GetBinCenter(ibin_end) < bin_hi )
      ibin_end++;
    for ( int i=ibin_begin; i<ibin_end; i++ )
      nevents += pow(hst->GetBinError(i),2);
    nevents = sqrt(nevents);
    return nevents;
}
void decorate(TGraph *h, TString gtitle, float gmax, float gmin, 
	      int markercolor, int markerstyle, int linecolor, int linewidth)
{
  h->SetTitle(gtitle);
  h->SetMarkerColor(markercolor); h->SetMarkerStyle(markerstyle);
  h->SetLineColor(linecolor); h->SetLineWidth(linewidth);
  h->SetMaximum(gmax); h->SetMinimum(gmin);
}
void decorateHist(TH1*h,const char* xtitle, const char* ytitle, const char* title,
		  int linecolor, int linewidth, int markercolor, int markerstyle, int tofill) {
  
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  
  h->SetLineColor(linecolor); 
  h->SetLineWidth(linewidth);
  h->SetMarkerColor(markercolor);
  h->SetMarkerStyle(markerstyle);
  if(tofill==1) h->SetFillColor(markercolor);

  h->SetMarkerSize(1.1);
  h->SetTitle(title);
}

void decorate(TLegend *g, float textSize, TString legendheader)
{
  g->SetTextSize(textSize);
  g->SetFillStyle(2);
  g->SetFillColor(4);
  g->SetBorderSize(1);
  g->SetLineColor(0);
  //Usually legends should not have headers
  //but if you want one, uncomment the next line.
  //g->SetHeader(legendheader);
}

void SetOverflowBin(TH1F *histo)
{
  int nbins;
  nbins = histo->GetNbinsX();
  histo->SetBinContent(nbins, histo->GetBinContent(nbins) + histo->GetBinContent(nbins+100));//Overflow
  histo->SetBinContent(1, histo->GetBinContent(1)+ histo->GetBinContent(-100));//Underflow
}
