void RData_103()
{
   // We prepared an input tree to run on
   //auto fileName = "dst6535_es_MC_60nA.root";
   //auto fileName = "../../02DVCS_Analysis/auto_bin_analysis/dst6535_all_e_test.root";
   //auto fileName = "../../02DVCS_Analysis/Fiducal_cut/dst6535_data.root";
   auto fileName = "output.root";
   auto treeName = "trackTree";
 
   ROOT::RDataFrame dQ2(treeName, fileName, {"Q2"});
   ROOT::RDataFrame dElectron_P(treeName, fileName, {"Electron_Px", "Electron_Py", "Electron_Pz"});

   auto cutQ2 = [](double Q2) { return Q2 > 0.; };
   auto entries1 = dQ2.Filter(cutQ2, {"Q2"})
                    .Count();
   std::cout << *entries1 << " entries passed all filters" << std::endl;

   auto histQ2 = dQ2.Filter(cutQ2).Histo1D();
   //or
   TH1F histQ2DIY("histQ2DIY", "histQ2DIY", 100, 0, 3);
   dQ2.Filter(cutQ2, {"Q2"}).Foreach([&histQ2DIY](double Q2) { histQ2DIY.Fill(Q2); });
   
   TCanvas canvas("canvas", "Histogram Canvas", 1920, 1200);
   histQ2->Draw();
   canvas.SaveAs("RData_103_1.png");

   TCanvas canvas2("canvas2", "Histogram Canvas", 1920, 1200);
   histQ2DIY.Draw();
   canvas2.SaveAs("RData_103_2.png");


   TH1F histElectronPx("histElectronPx", "histElectronPx", 500, -1.5, 1.5);
   dElectron_P.Foreach([&histElectronPx](vector<float> Electron_Px) { histElectronPx.Fill(Electron_Px[0]); });

   TH1F histElectronPy("histElectronPy", "histElectronPy", 500, -1.5, 1.5);
   dElectron_P.Foreach([&histElectronPy](vector<float> Electron_Px, vector<float> Electron_Py) { histElectronPy.Fill(Electron_Py[0]); });

   TH2F histElectronPxPy("histElectronPxPy", "histElectronPxPy", 500, -1.5, 1.5, 500, -1.5, 1.5);
   dElectron_P.Foreach([&histElectronPxPy](vector<float> Electron_Px, vector<float> Electron_Py) { 
      histElectronPxPy.Fill(Electron_Px[0], Electron_Py[0]); 
   });

   TCanvas canvas3("canvas3", "Histogram Canvas", 1920, 1200);
   histElectronPx.Draw();
   canvas3.SaveAs("RData_103_3.png");

   TCanvas canvas4("canvas4", "Histogram Canvas", 1920, 1200);
   histElectronPy.Draw();
   canvas4.SaveAs("RData_103_4.png");
   
   TCanvas canvas5("canvas5", "Histogram Canvas", 1920, 1200);
   histElectronPxPy.Draw();
   canvas5.SaveAs("RData_103_5.png");


   gApplication->Terminate(0);
}