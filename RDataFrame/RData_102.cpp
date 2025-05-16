// ## Preparation
 
// A simple helper function to fill a test tree: this makes the example
// stand-alone.
void fill_tree(const char *treeName, const char *fileName)
{
   ROOT::RDataFrame d(10);
   d.Define("b1", [](ULong64_t entry) -> double { return entry; }, {"rdfentry_"})
    .Define("b2", [](ULong64_t entry) -> int { return entry * entry; }, {"rdfentry_"})
    .Snapshot(treeName, fileName);
}
 
int RData_102()
{
 
   // We prepare an input tree to run on
   auto fileName = "RData_102.root";
   auto treeName = "RDataTree";
   fill_tree(treeName, fileName);
 
   ROOT::RDataFrame d(treeName, fileName, {"b1"});

   auto cutb1 = [](double b1) { return b1 < 5.; };
   auto cutb1b2 = [](int b2, double b1) { return b2 % 2 && b1 < 4.; };
   auto entries1 = d.Filter(cutb1, {"b1"})
                    .Filter(cutb1b2, {"b2", "b1"})
                    .Count();
   std::cout << *entries1 << " entries passed all filters" << std::endl;
 
   auto entries2 = d.Filter("b1 < 4.").Count();
   std::cout << *entries2 << " entries passed the string filter" << std::endl;
 
   auto b1b2_cut = d.Filter("b1 < 4");
   auto minVal = b1b2_cut.Min();
   auto maxVal = b1b2_cut.Max();
   auto meanVal = b1b2_cut.Mean();
   auto nonDefmeanVal = b1b2_cut.Mean("b2"); // <- Column is not the default
   std::cout << "The mean is always included between the min and the max: " << *minVal << " <= " << *meanVal
             << " <= " << *maxVal << std::endl;
 
   auto b1_cut = d.Filter(cutb1);
   auto b1Vec = b1_cut.Take<double>();
   auto b1List = b1_cut.Take<double, std::list<double>>();
 
   std::cout << "Selected b1 entries" << std::endl;
   for (auto b1_entry : *b1List)
      std::cout << b1_entry << " ";
   std::cout << std::endl;
   auto b1VecCl = ROOT::GetClass(b1Vec.GetPtr());
   std::cout << "The type of b1Vec is " << b1VecCl->GetName() << std::endl;
 
   auto hist = d.Filter(cutb1).Histo1D();
   std::cout << "Filled h " << hist->GetEntries() << " times, mean: " << hist->GetMean() << std::endl;
 
   TH1F h("h", "h", 12, -1, 11);
   d.Filter([](int b2) { return b2 % 2 == 0; }, {"b2"}).Foreach([&h](double b1) { h.Fill(b1); });
 
   std::cout << "Filled h with " << h.GetEntries() << " entries" << std::endl;
 
   auto cutb1_result = d.Filter(cutb1);
   auto cutb1b2_result = d.Filter(cutb1b2, {"b2", "b1"});
   auto cutb1_cutb1b2_result = cutb1_result.Filter(cutb1b2, {"b2", "b1"});
   // Now we want to count:
   auto evts_cutb1_result = cutb1_result.Count();
   auto evts_cutb1b2_result = cutb1b2_result.Count();
   auto evts_cutb1_cutb1b2_result = cutb1_cutb1b2_result.Count();
 
   std::cout << "Events passing cutb1: " << *evts_cutb1_result << std::endl
             << "Events passing cutb1b2: " << *evts_cutb1b2_result << std::endl
             << "Events passing both: " << *evts_cutb1_cutb1b2_result << std::endl;
 
   auto entries_sum = d.Define("sum", [](double b1, int b2) { return b2 + b1; }, {"b1", "b2"})
                         .Filter([](double sum) { return sum > 4.2; }, {"sum"})
                         .Count();
   std::cout << *entries_sum << std::endl;
 
   auto entries_sum2 = d.Define("sum2", "b1 + b2").Filter("sum2 > 4.2").Count();
   std::cout << *entries_sum2 << std::endl;
 
   auto printEntrySlot = [](ULong64_t iEntry, unsigned int slot) {
      std::cout << "Entry: " << iEntry << " Slot: " << slot << std::endl;
   };
   d.Foreach(printEntrySlot, {"rdfentry_", "rdfslot_"});
 
   return 0;
}