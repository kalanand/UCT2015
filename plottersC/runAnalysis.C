{

  //..
  //  L1Rate and UCTRate analyzers take ( name_of_input_file, name_of_ntuple/tree )

  L1RateTree * l1 = new L1RateTree("../rate_tree_muon_PU66_merged.root","muonL1Rate/Ntuple" );
  l1->Loop();


  //////
  UCTRateTree * uct = new UCTRateTree("../rate_tree_muon_PU66_merged.root","jetUCTRate/Ntuple" );
  uct->Loop();
  
  uct->CombinePlots( );
  uct->CombineL1UCT( l1->h_rate );

  //delete uct;
  //delete l1;
  

}
