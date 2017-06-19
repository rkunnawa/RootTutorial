{
  //! Raghav Kunnawalkam Elayavalli
  //! Rutgers University
  //! June 8th 2017
  //! raghav@physics.rutgers.edu 

  //! readtextfile - to read a text file and make a histogram

  TCanvas * ctest = new TCanvas("ctest", "Tutorial", 600, 600);
  ctest->Divide(2,1);
  
  TGraphErrors graph_input("./macro2_input.txt","%lg %lg %lg");
  graph_input.SetTitle("Measurement;length [cm];Arb.Units");
  graph_input.SetFillColor(3);
  ctest->cd(1);
  graph_input.Draw("ACP");

  ifstream fin;
  fin.open("macro2_input.txt");
  int x;
  double y;
  int ey;
  TH1F * htest = new TH1F("htest", "Measurement;length (cm);arb.units", 10, 0, 10);
  while(1){
    fin >> x >> y >> ey;
    // cout << "x = " << x << endl;
    htest->SetBinContent(x, y);
    htest->SetBinError(x, ey);    
    if(!fin.good()) break;
  }
  ctest->cd(2);
  htest->Draw("BAR");

  ctest->SaveAs("testplot.pdf", "RECREATE");

  TFile * fout = new TFile("testfile.root", "RECREATE");
  fout->cd();
  
  graph_input.SetName("mytestGraph");
  graph_input.Write();

  htest->SetName("mytestHisto");
  htest->Write();

  fout->Close();

  
  
}
