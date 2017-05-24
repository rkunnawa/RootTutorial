/*
Ian Hunt-Isaak
ihuntisa@oberlin.edu
Macro to learn to utilize root selection criteria
Requires pp_2013_data_testfile.root to be in the same directory
 */
#include "TCanvas.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

Float_t jtpt_ak3[1000];
Float_t jteta_ak3[1000];
Float_t jtphi_ak3[1000];
Int_t jt80;
Int_t jt60;
Int_t jt40;
Int_t jt80_pre;
Int_t jt60_pre;
Int_t jt40_pre;
Int_t njets_ak3;

void pp_criteria(){

  
  // Create file which will have histograms written into it
 
  //Define and Divide Canvas
  TCanvas * c = new TCanvas("c","Selection Cuts",1200,800);
  c -> Divide(3,1); // divides canvas into 3 columns and 1 row

  //Define Histograms
  TH1F * h80 = new TH1F("h80","Jet p_{T} (GeV/c)>80;Jet p_{T};# Counts",100,0,500);
  TH1F * h60 = new TH1F("h60","Jet p_{T} (GeV/c)>60;Jet p_{T};# Counts",100,0,500);
  TH1F * h40 = new TH1F("h40","Jet p_{T} (GeV/c)>40;Jet p_{T};# Counts",100,0,500);

  //Access File
  TFile * fileA = TFile::Open("pp_2013_data_testfile.root");//hardcoded to load this file
  
  //Create Trees
  TTree * hlt = (TTree*)fileA->Get("hltanalysis/HltTree"); // high level triggering tree
  TTree * ak3t = (TTree*)fileA->Get("akPu3PFJetAnalyzer/t");// jet data

  //Add Friends
  ak3t ->AddFriend(hlt); // this allows the ak3t tree to access the variables in the tree hlt
 
  int Nevents = ak3t->GetEntries();

  //Setting Branch addresses
      //variables 
  ak3t->SetBranchAddress("jtpt",jtpt_ak3);
  ak3t->SetBranchAddress("jteta",jteta_ak3);
  ak3t->SetBranchAddress("jtphi",jtphi_ak3);
  ak3t->SetBranchAddress("nref",&njets_ak3);

      //Selection cut criteria. Event variable {0,1}
      //HLT_PAJet#_NoJetID_v1 = 1 if there was at least one Jet with pT>#. Otherwise = 0 
  ak3t->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&jt80);
  ak3t->SetBranchAddress("HLT_PAJet60_NoJetID_v1",&jt60);
  ak3t->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&jt40);

      //prescales - account for fact that not all events passing the trigger are recorded
      //filling histograms will need to be weighted by the prescale values
  ak3t->SetBranchAddress("HLT_PAJet80_NoJetID_v1_Prescl",&jt80_pre);
  ak3t->SetBranchAddress("HLT_PAJet60_NoJetID_v1_Prescl",&jt60_pre);
  ak3t->SetBranchAddress("HLT_PAJet40_NoJetID_v1_Prescl",&jt40_pre);

  for(int iev = 0; iev < Nevents; ++iev){ /// loop through the events 
    ak3t->GetEntry(iev);

    for(int i = 0; i < njets_ak3; ++i){//loop through the events in a jet
      if(jt80)
	h80 -> Fill(jtpt_ak3[i],jt80_pre);
      if(jt60)
	h60 -> Fill(jtpt_ak3[i],jt60_pre);
      if(jt40)
	h40 -> Fill(jtpt_ak3[i],jt40_pre);
    }
  }

  TFile f("selectionCriteria.root","RECREATE");
  c->cd(1);
  c->cd(1)->SetLogy();


  h80->Draw();

  c->cd(2);
  c->cd(2)->SetLogy();

  h60->Draw("HIST");  
 
  c->cd(3);
  c->cd(3)->SetLogy();

  
  h40->Draw("HIST");

  c->SaveAs("4plots.pdf","Recreate");
  f.Write(); // write f to save the histograms
}
