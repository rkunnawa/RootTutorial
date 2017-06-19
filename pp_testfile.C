/*
Ian Hunt-Isaak
ihuntisa@oberlin.edu
Outputs a histogram of the difference between the leading jet and all other jets.
Accomplishes this using the Draw command. This is the most basic way to do this.
Requires pp_2013_data_testfile.root to be in the same directory
*/

#include "TCanvas.h"
#include "TFile.h"

void pp_testfile(){

  TFile * _raghav = TFile::Open("pp_2013_data_testfile.root");

  TCanvas * c = new TCanvas("c","4 Plots",1);
  c -> Divide(2,2);
  TTree *ak3t = (TTree*)_raghav -> Get("ak3PFJetAnalyzer/t");
  TH1F * hPt = new TH1F("hPt","Jet p_{T} (GeV/c)",100,0,1000);
  TH1F * hEta = new TH1F("hEta","Jet #eta (rad)",60,-2,2);
  TH1F * hPhi = new TH1F ("hPhi","Jet #phi (rad)",60,-3.14,3.14);
  TH2F * hAll = new TH2F("hAll","Jet #phi (rad):Jet #eta (rad):Jet p_{T} (rad)",60,-2,2,60,-3.14,+3.14);
  ak3t -> Draw("jtpt>>hPt","","goff");
  ak3t -> Draw("jteta>>hEta","","goff");
  ak3t -> Draw("jtphi>>hPhi","","goff");
  ak3t -> Draw("jtphi:jteta>>hAll","jtpt>10","goff");
  c->cd(1);
  hPt->Draw();

  c->cd(2);
  hEta->Draw();  

  c->cd(3);
  hPhi->Draw();
  c->cd(4);
  hAll->Draw("LEGO");
  c -> SaveAs("4plots.pdf","RECREATE");
 
}
