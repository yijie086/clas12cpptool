void RData_104()
{
   // We prepared an input tree to run on
   //auto fileName = "dst6535_es_MC_60nA.root";
   //auto fileName = "../../02DVCS_Analysis/auto_bin_analysis/dst6535_all_e_test.root";
   //auto fileName = "../../02DVCS_Analysis/Fiducal_cut/dst6535_data.root";
   auto fileName = "output.root";
   auto treeName = "trackTree";
 
   ROOT::RDataFrame dPP_theta(treeName, fileName, {"Proton_theta", "Photon_theta"});

   TH1F histProton_theta("Proton_theta", "Proton_theta", 500, 0, 100);
   dPP_theta.Foreach([&histProton_theta](vector<float> Proton_theta) { histProton_theta.Fill(Proton_theta[0]); });
   TCanvas canvas("canvas", "Histogram Canvas", 1920, 1200);
   histProton_theta.Draw();
   canvas.SaveAs("RData_104_1.png");

   TH1F histPhoton_theta("Photon_theta", "Photon_theta", 500, 0, 35);
   dPP_theta.Foreach([&histPhoton_theta](vector<float> Proton_theta, vector<float> Photon_theta) { histPhoton_theta.Fill(Photon_theta[0]); });
   TCanvas canvas2("canvas2", "Histogram Canvas", 1920, 1200);
   histPhoton_theta.Draw();
   canvas2.SaveAs("RData_104_2.png");

   TH2D histProton_theta_Photon_theta("Proton_theta_Photon_theta", "Proton_theta_Photon_theta", 500, 0, 35, 500, 0, 100);
   dPP_theta.Foreach([&histProton_theta_Photon_theta](vector<float> Proton_theta, vector<float> Photon_theta) { 
      histProton_theta_Photon_theta.Fill(Photon_theta[0], Proton_theta[0]); 
   });
   TCanvas canvas3("canvas3", "Histogram Canvas", 1920, 1200);
   histProton_theta_Photon_theta.Draw("COLZ");
   gPad->SetLogz();
   canvas3.SaveAs("RData_104_3.png");

   gApplication->Terminate(0);
}