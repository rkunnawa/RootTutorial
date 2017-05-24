/*
Ian Hunt-Isaak
ihuntisa@oberlin.edu
Generates histograms of jtpt, jteta,jtphi and a 2D histogram of jtphi vs jteta 
This is accomplished by looping through the events and the jets in each event.
Requires pp_2013_data_testfile.root to be in the same directory
 */

#include "TCanvas.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"

Float_t jtpt_ak3[1000];
Float_t jteta_ak3[1000];
Float_t jtphi_ak3[1000];
Int_t njets_ak3;

void pp_loop(){
  TCanvas * c = new TCanvas("c","4 Plots",1);
  c -> Divide(2,2);

  TH1F * hPt = new TH1F("hPt","Jet p_{T} (GeV/c)",100,0,1000);
  TH1F * hEta = new TH1F("hEta","Jet #eta (rad)",60,-2,2);
  TH1F * hPhi = new TH1F ("hPhi","Jet #phi (rad)",100,-3.14,3.14);
  TH2F * h2d = new TH2F("h2d","Jet #phi (rad):Jet #eta (rad)",60,-2,2,60,-3.14,+3.14);

  TFile * fileA = TFile::Open("pp_2013_data_testfile.root");
  TTree * t = (TTree*)fileA->Get("hltanalysis/HltTree");
  TTree * ak3t = (TTree*)fileA->Get("akPu3PFJetAnalyzer/t");

  int Nevents = t->GetEntries();
  
  ak3t->SetBranchAddress("jtpt",jtpt_ak3);
  ak3t->SetBranchAddress("jteta",jteta_ak3);
  ak3t->SetBranchAddress("jtphi",jtphi_ak3);
  ak3t->SetBranchAddress("nref",&njets_ak3);
  
  for(int iev = 0; iev < Nevents; ++iev){
    t->GetEntry(iev);
    ak3t->GetEntry(iev);

    for(int i = 0; i < njets_ak3; ++i){
      hPt->Fill(jtpt_ak3[i]);
      hEta->Fill(jteta_ak3[i]);
      hPhi->Fill(jtphi_ak3[i]);
      if(jtpt_ak3[i]>40)
	h2d->Fill(jtphi_ak3[i],jteta_ak3[i]);
    }
  }
  hPt->Scale(1./Nevents);
  hEta->Scale(1./Nevents);
  hPhi ->Scale(1./Nevents);
  
  TFile f("test.root","RECREATE");

  c->cd(1);
  c->cd(1)->SetLogy();

  hPt->GetXaxis()->SetTitle("Jet p_{T}");
  hPt->GetYaxis()->SetTitle("# Counts Per Event");
  hPt->Draw();

  c->cd(2);
  c->cd(2)->SetLogy();

  hEta->GetXaxis()->SetTitle("Jet #Eta");
  hEta->GetYaxis()->SetTitle("# Counts Per Event");
  hEta->Draw();  

  c->cd(3);
  c->cd(3)->SetLogy();

  hPhi->GetXaxis()->SetTitle("Jet #Phi");
  hPhi->GetYaxis()->SetTitle("# Counts Per Event");
  hPhi->Draw();
  
  c->cd(4);
  h2d->Draw("LEGO");
  c->SaveAs("4plots2.pdf","Recreate");
  f.Write();
}
