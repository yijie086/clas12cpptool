void RData_101()
{
   // Create a data frame with 100 rows
   ROOT::RDataFrame rdf(100);
 
   // Define a new column `x` that contains random numbers
   auto rdf_x = rdf.Define("x", [](){ return gRandom->Rndm(); });
 
   // Create a histogram from `x`
   auto h = rdf_x.Histo1D("x");
 
   // Create a canvas to draw the histogram
   TCanvas canvas("canvas", "Histogram Canvas", 1920, 1200);

   // At the end of this function, the histogram pointed to by `h` will be deleted.
   // Draw a copy of the histogram object instead:
   h->DrawClone();
   
   // Save the canvas as an image file
   canvas.SaveAs("RData_101.png");

   gApplication->Terminate(0);
}