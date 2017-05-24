{

   ifstream in;
   in.open("distribution.txt");

   double x, y;
   TH1F * hX = new TH1F("hX","",55, -10, 100);
   TH1F * hY = new TH1F("hY","",55, -10, 100);

   while (1) {
     in >> x >> y; 
     if (!in.good()) break;
     hX->Fill(x);
     hY->Fill(y);
   }

   TCanvas * c = new TCanvas("c", "", 400, 400);
   c->cd();
   hX->SetLineColor(kRed);   
   hX->Draw();
   hY->SetLineColor(kBlue);   
   hY->Draw("same");
   c->SaveAs("test.pdf","RECREATE");
}
