/*

  Raghav Kunnawalkam Elayavalli
  Rutgers University
  June 9th 2017 

  readrootfile.C 
  Test code that compiles and reads root file and makes histograms from trees 

*/

#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"

void readrootfile(){

  gStyle->SetOptStat(0);
  
  //! Load the input file
  TFile * fInput1 = TFile::Open("testfile.root");
  TFile * fInput2 = TFile::Open("events.root");

  //! get histograms/trees from file
  TH1F * hMeasurement = (TH1F*)fInput1->Get("mytestHisto");
  TTree * tevt = (TTree*)fInput2->Get("events");

  TH1F * hTrackX = new TH1F("hTrackX",
			    "", 100, -30, 30);
  TH1F * hTrackY = new TH1F("hTrackY",
			    "", 100, -30, 30);
  TH1F * hTrackZ = new TH1F("hTrackZ",
			    "", 100, -30, 30);
  TH1F * hTrackT = new TH1F("hTrackT",
			    "", 100, 0, 100);

  //! Draw histograms from the tree
  tevt->Draw("tracks.fCoordinates.fX>>hTrackX"
	     , "", "goff");
  tevt->Draw("tracks.fCoordinates.fY>>hTrackY"
	     , "", "goff");
  tevt->Draw("tracks.fCoordinates.fZ>>hTrackZ"
	     , "", "goff");
  tevt->Draw("tracks.fCoordinates.fT>>hTrackT"
	     , "", "goff");

  //! Create canvas
  TCanvas * cMeas = new TCanvas("cMeas",  "",
				900, 300);
  cMeas->Divide(3, 1);
  cMeas->cd(1);
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gPad->SetTickx();
  gPad->SetTicky();  
  hMeasurement->SetXTitle("Length [cm]");
  hMeasurement->SetMarkerStyle(23);
  hMeasurement->SetMarkerColor(kRed);
  hMeasurement->Draw("p");

  cMeas->cd(2);
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gPad->SetTickx();
  gPad->SetTicky();  
  hTrackX->SetXTitle("Track Position [cm]");
  hTrackX->SetMarkerStyle(25);
  hTrackX->SetMarkerColor(kRed);
  hTrackX->Draw("p");

  hTrackY->SetMarkerStyle(26);
  hTrackY->SetMarkerColor(kBlue);
  hTrackY->Draw("same p");

  hTrackZ->SetMarkerStyle(27);
  hTrackZ->SetMarkerColor(kGreen);
  hTrackZ->Draw("same p");

  TLegend * ltest = new TLegend(0.15, 0.4,
				0.4, 0.8);
  ltest->AddEntry(hTrackX, "X", "p");
  ltest->AddEntry(hTrackY, "Y", "p");
  ltest->AddEntry(hTrackZ, "Z", "p");
  ltest->SetTextSize(0.04);
  ltest->SetBorderSize(0);
  ltest->SetFillStyle(0);
  ltest->Draw();
  
  cMeas->cd(3);
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gPad->SetTickx();
  gPad->SetTicky();  
  hTrackT->SetXTitle("Track Time [sec]");
  hTrackT->SetMarkerStyle(25);
  hTrackT->SetMarkerColor(kRed);
  hTrackT->Draw("p");

  cMeas->SaveAs("measurement.pdf", "RECREATE");
  
}//! end of main analysis 
